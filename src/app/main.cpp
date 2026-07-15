#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QDebug>

// Services
#include "SimulatedCanBus.h"
#include "SimulatedAdasPipeline.h"
#include "SimulatedHvacHardware.h"
#include "LocalFileMediaProvider.h"
#include "YoloProcessingStrategy.h"

// ViewModels
#include "SpeedViewModel.h"
#include "RpmViewModel.h"
#include "TellTaleViewModel.h"
#include "AdasViewModel.h"
#include "HvacViewModel.h"
#include "MediaPlayerViewModel.h"
#include "VehicleSettingsViewModel.h"
#include "DashboardStateManager.h"
#include "WatchdogManager.h"

// Core
#include <core/DataIntegrity.h>
#include <core/VehicleData.h>
#include <core/AdasData.h>
#include <core/HvacData.h>
#include <core/MediaData.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName(QStringLiteral("HMI Dashboard"));
    QGuiApplication::setOrganizationName(QStringLiteral("Automotive HMI"));

    // Set the Basic style — we provide full custom styling
    QQuickStyle::setStyle(QStringLiteral("Basic"));

    // ── Register metatypes for cross-thread signal/slot ─────────────────
    qRegisterMetaType<hmi::SpeedData>("hmi::SpeedData");
    qRegisterMetaType<hmi::RpmData>("hmi::RpmData");
    qRegisterMetaType<hmi::TellTaleEvent>("hmi::TellTaleEvent");
    qRegisterMetaType<hmi::TellTaleId>("hmi::TellTaleId");
    qRegisterMetaType<hmi::TellTaleState>("hmi::TellTaleState");
    qRegisterMetaType<hmi::AdasFrame>("hmi::AdasFrame");
    qRegisterMetaType<hmi::HvacState>("hmi::HvacState");
    qRegisterMetaType<hmi::PlaybackState>("hmi::PlaybackState");
    qRegisterMetaType<hmi::TrackInfo>("hmi::TrackInfo");

    // ── Dependency Injection: Create concrete service implementations ───
    hmi::SimulatedCanBus        canBus;
    hmi::SimulatedAdasPipeline  adasPipeline;
    hmi::SimulatedHvacHardware  hvacHardware;
    hmi::LocalFileMediaProvider mediaProvider;
    hmi::DataIntegrity          dataIntegrity;

    // ── Create ViewModels ───────────────────────────────────────────────
    hmi::SpeedViewModel          speedVm;
    hmi::RpmViewModel            rpmVm;
    hmi::TellTaleViewModel       tellTaleVm;
    hmi::AdasViewModel           adasVm;
    hmi::HvacViewModel           hvacVm;
    hmi::MediaPlayerViewModel    mediaVm;
    hmi::VehicleSettingsViewModel settingsVm;
    hmi::DashboardStateManager   stateManager;

    // ── Inject dependencies ─────────────────────────────────────────────
    // Strategy pattern: set YOLO processing for ADAS
    adasVm.setProcessingStrategy(std::make_unique<hmi::YoloProcessingStrategy>(0.5f, 0.45f));

    // HVAC ViewModel ← HVAC controller
    hvacVm.setController(&hvacHardware);

    // Media ViewModel ← Media provider
    mediaVm.setProvider(&mediaProvider);

    // ── Connect vehicle bus → ViewModels (Observer pattern via Signals/Slots) ──
    // Data integrity validation is done inline via lambda
    QObject::connect(&canBus, &hmi::IVehicleBus::speedDataReceived,
                     &speedVm, [&dataIntegrity, &speedVm](const hmi::SpeedData &data) {
        if (dataIntegrity.validateSpeed(data)) {
            speedVm.onSpeedChanged(data.kmh);
        }
    });

    QObject::connect(&canBus, &hmi::IVehicleBus::rpmDataReceived,
                     &rpmVm, [&dataIntegrity, &rpmVm](const hmi::RpmData &data) {
        if (dataIntegrity.validateRpm(data)) {
            rpmVm.onRpmChanged(data.rpm, data.gear);
        }
    });

    QObject::connect(&canBus, &hmi::IVehicleBus::tellTaleChanged,
                     &tellTaleVm, [&dataIntegrity, &tellTaleVm](const hmi::TellTaleEvent &event) {
        if (dataIntegrity.validateTellTale(event)) {
            tellTaleVm.onTellTaleChanged(event.id, event.state);
        }
    });

    // ADAS pipeline → ADAS ViewModel
    QObject::connect(&adasPipeline, &hmi::IAdasSensor::frameReceived,
                     &adasVm, &hmi::AdasViewModel::onFrameReceived);

    // ── Watchdog for functional safety ──────────────────────────────────
    hmi::WatchdogManager watchdog(&stateManager);

    // ── Expose ViewModels to QML (via context properties for singleton VMs) ──
    QQmlApplicationEngine engine;

    QQmlContext *ctx = engine.rootContext();
    ctx->setContextProperty(QStringLiteral("speedViewModel"), &speedVm);
    ctx->setContextProperty(QStringLiteral("rpmViewModel"), &rpmVm);
    ctx->setContextProperty(QStringLiteral("tellTaleViewModel"), &tellTaleVm);
    ctx->setContextProperty(QStringLiteral("adasViewModel"), &adasVm);
    ctx->setContextProperty(QStringLiteral("hvacViewModel"), &hvacVm);
    ctx->setContextProperty(QStringLiteral("mediaViewModel"), &mediaVm);
    ctx->setContextProperty(QStringLiteral("settingsViewModel"), &settingsVm);
    ctx->setContextProperty(QStringLiteral("dashboardState"), &stateManager);

    // ── Load QML ────────────────────────────────────────────────────────
    const QUrl url(QStringLiteral("qrc:/qt/qml/HmiDashboard/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    // ── Start all services ──────────────────────────────────────────────
    canBus.start();
    adasPipeline.start();
    watchdog.start();
    mediaProvider.play();  // auto-start demo playback

    qDebug() << "═══════════════════════════════════════════════";
    qDebug() << "  Automotive HMI Dashboard v1.0";
    qDebug() << "  Vehicle Bus:   SimulatedCanBus (50 Hz)";
    qDebug() << "  ADAS Pipeline: SimulatedAdasPipeline (10 Hz)";
    qDebug() << "  ADAS Strategy: YOLO NMS";
    qDebug() << "  Watchdog:      500ms timeout";
    qDebug() << "═══════════════════════════════════════════════";

    int result = app.exec();

    // ── Cleanup ─────────────────────────────────────────────────────────
    canBus.stop();
    adasPipeline.stop();
    watchdog.stop();

    return result;
}
