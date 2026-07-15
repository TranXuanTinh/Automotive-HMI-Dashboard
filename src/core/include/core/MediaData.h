#ifndef CORE_MEDIADATA_H
#define CORE_MEDIADATA_H

#include <cstdint>
#include <QString>
#include <QUrl>
#include <QMetaType>

namespace hmi {

// ── Media playback state ────────────────────────────────────────────────
enum class PlaybackState : uint8_t {
    Stopped = 0,
    Playing,
    Paused
};

// ── Track metadata ──────────────────────────────────────────────────────
struct TrackInfo {
    QString title;
    QString artist;
    QString album;
    QUrl    albumArtUrl;
    qint64  durationMs = 0;
};

} // namespace hmi

Q_DECLARE_METATYPE(hmi::PlaybackState)
Q_DECLARE_METATYPE(hmi::TrackInfo)

#endif // CORE_MEDIADATA_H
