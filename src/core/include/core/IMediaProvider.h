#ifndef CORE_IMEDIAPROVIDER_H
#define CORE_IMEDIAPROVIDER_H

#include <QObject>
#include <QStringList>
#include "MediaData.h"

namespace hmi {

/// Abstract interface for media sources (local files, Bluetooth, USB, streaming).
/// Adding a new source means implementing this interface — Open/Closed Principle:
/// no existing playback logic is modified.
class IMediaProvider : public QObject
{
    Q_OBJECT

public:
    explicit IMediaProvider(QObject *parent = nullptr) : QObject(parent) {}
    ~IMediaProvider() override = default;

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual void seek(qint64 positionMs) = 0;
    virtual void setVolume(float volume) = 0;  // 0.0–1.0

    virtual PlaybackState playbackState() const = 0;
    virtual TrackInfo currentTrack() const = 0;
    virtual qint64 position() const = 0;
    virtual float volume() const = 0;

    /// Human-readable source name ("Local Files", "Bluetooth", etc.)
    virtual QString sourceName() const = 0;

signals:
    void playbackStateChanged(hmi::PlaybackState state);
    void trackChanged(const hmi::TrackInfo &track);
    void positionChanged(qint64 positionMs);
    void volumeChanged(float volume);
    void mediaError(const QString &description);
};

} // namespace hmi

#endif // CORE_IMEDIAPROVIDER_H
