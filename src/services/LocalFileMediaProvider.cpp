#include "LocalFileMediaProvider.h"

namespace hmi {

LocalFileMediaProvider::LocalFileMediaProvider(QObject *parent)
    : IMediaProvider(parent)
{
    // Demo playlist with realistic track metadata
    m_playlist = {
        { QStringLiteral("Midnight Drive"),     QStringLiteral("Synthwave Rider"),  QStringLiteral("Neon Highways"),      234000 },
        { QStringLiteral("Electric Dreams"),    QStringLiteral("RetroFuture"),      QStringLiteral("Chrome & Steel"),     198000 },
        { QStringLiteral("Dashboard Lights"),   QStringLiteral("The Engineers"),    QStringLiteral("Instrument Panel"),   267000 },
        { QStringLiteral("Highway Zero"),       QStringLiteral("Velocity"),         QStringLiteral("Redline"),            312000 },
        { QStringLiteral("Turbo Boost"),        QStringLiteral("Engine Sound"),     QStringLiteral("Under The Hood"),     189000 },
        { QStringLiteral("Night Cruise"),       QStringLiteral("City Lights"),      QStringLiteral("Urban Drive"),        245000 },
        { QStringLiteral("Acceleration"),       QStringLiteral("Torque Band"),      QStringLiteral("Full Throttle"),      278000 },
    };

    m_positionTimer.setInterval(100);  // update position every 100ms
    connect(&m_positionTimer, &QTimer::timeout, this, &LocalFileMediaProvider::updatePosition);

    loadTrack(0);
}

void LocalFileMediaProvider::play()
{
    if (m_state == PlaybackState::Playing) return;
    m_state = PlaybackState::Playing;
    m_positionTimer.start();
    emit playbackStateChanged(m_state);
}

void LocalFileMediaProvider::pause()
{
    if (m_state != PlaybackState::Playing) return;
    m_state = PlaybackState::Paused;
    m_positionTimer.stop();
    emit playbackStateChanged(m_state);
}

void LocalFileMediaProvider::stop()
{
    m_state = PlaybackState::Stopped;
    m_position = 0;
    m_positionTimer.stop();
    emit playbackStateChanged(m_state);
    emit positionChanged(m_position);
}

void LocalFileMediaProvider::next()
{
    int nextIndex = (m_currentIndex + 1) % m_playlist.size();
    loadTrack(nextIndex);
    if (m_state == PlaybackState::Playing)
        m_positionTimer.start();
}

void LocalFileMediaProvider::previous()
{
    // If more than 3 seconds in, restart current track; otherwise go to previous
    if (m_position > 3000) {
        seek(0);
        return;
    }
    int prevIndex = (m_currentIndex - 1 + m_playlist.size()) % m_playlist.size();
    loadTrack(prevIndex);
    if (m_state == PlaybackState::Playing)
        m_positionTimer.start();
}

void LocalFileMediaProvider::seek(qint64 positionMs)
{
    m_position = std::clamp(positionMs, qint64(0), m_currentTrack.durationMs);
    emit positionChanged(m_position);
}

void LocalFileMediaProvider::setVolume(float volume)
{
    m_volume = std::clamp(volume, 0.0f, 1.0f);
    emit volumeChanged(m_volume);
}

PlaybackState LocalFileMediaProvider::playbackState() const { return m_state; }
TrackInfo LocalFileMediaProvider::currentTrack() const { return m_currentTrack; }
qint64 LocalFileMediaProvider::position() const { return m_position; }
float LocalFileMediaProvider::volume() const { return m_volume; }

void LocalFileMediaProvider::updatePosition()
{
    m_position += 100;  // advance by timer interval
    if (m_position >= m_currentTrack.durationMs) {
        next();  // auto-advance to next track
        return;
    }
    emit positionChanged(m_position);
}

void LocalFileMediaProvider::loadTrack(int index)
{
    m_currentIndex = index;
    m_position = 0;

    const auto &track = m_playlist[index];
    m_currentTrack.title = track.title;
    m_currentTrack.artist = track.artist;
    m_currentTrack.album = track.album;
    m_currentTrack.durationMs = track.durationMs;

    emit trackChanged(m_currentTrack);
    emit positionChanged(m_position);
}

} // namespace hmi
