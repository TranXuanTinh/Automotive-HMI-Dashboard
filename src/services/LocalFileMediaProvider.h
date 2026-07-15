#ifndef SERVICES_LOCALFILEMEDIAPROVIDER_H
#define SERVICES_LOCALFILEMEDIAPROVIDER_H

#include <core/IMediaProvider.h>
#include <QTimer>
#include <QStringList>

namespace hmi {

/// Media provider for local file playback.
/// Simulates audio playback with a timer-based position tracker
/// (real Qt Multimedia integration can be added later without changing the interface).
class LocalFileMediaProvider : public IMediaProvider
{
    Q_OBJECT

public:
    explicit LocalFileMediaProvider(QObject *parent = nullptr);

    void play() override;
    void pause() override;
    void stop() override;
    void next() override;
    void previous() override;
    void seek(qint64 positionMs) override;
    void setVolume(float volume) override;

    PlaybackState playbackState() const override;
    TrackInfo currentTrack() const override;
    qint64 position() const override;
    float volume() const override;
    QString sourceName() const override { return QStringLiteral("Local Files"); }

private slots:
    void updatePosition();

private:
    void loadTrack(int index);

    struct DemoTrack {
        QString title;
        QString artist;
        QString album;
        qint64  durationMs;
    };

    QList<DemoTrack> m_playlist;
    int              m_currentIndex = 0;
    PlaybackState    m_state = PlaybackState::Stopped;
    TrackInfo        m_currentTrack;
    qint64           m_position = 0;
    float            m_volume = 0.7f;
    QTimer           m_positionTimer;
};

} // namespace hmi

#endif // SERVICES_LOCALFILEMEDIAPROVIDER_H
