#include "MediaPlayerViewModel.h"
#include <core/IMediaProvider.h>

namespace hmi {

MediaPlayerViewModel::MediaPlayerViewModel(QObject *parent)
    : QObject(parent)
{
}

void MediaPlayerViewModel::setProvider(IMediaProvider *provider)
{
    m_provider = provider;
    if (m_provider) {
        connect(m_provider, &IMediaProvider::trackChanged,
                this, &MediaPlayerViewModel::onTrackChanged);
        connect(m_provider, &IMediaProvider::positionChanged,
                this, &MediaPlayerViewModel::onPositionChanged);
        connect(m_provider, &IMediaProvider::playbackStateChanged,
                this, &MediaPlayerViewModel::onPlaybackStateChanged);
        connect(m_provider, &IMediaProvider::volumeChanged,
                this, &MediaPlayerViewModel::onVolumeChanged);

        m_track = m_provider->currentTrack();
        m_position = m_provider->position();
        m_volume = m_provider->volume();
        emit trackChanged();
    }
}

double MediaPlayerViewModel::progress() const
{
    if (m_track.durationMs <= 0) return 0.0;
    return static_cast<double>(m_position) / static_cast<double>(m_track.durationMs);
}

QString MediaPlayerViewModel::durationText() const { return formatTime(m_track.durationMs); }
QString MediaPlayerViewModel::positionText() const { return formatTime(m_position); }

void MediaPlayerViewModel::play()      { if (m_provider) m_provider->play(); }
void MediaPlayerViewModel::pause()     { if (m_provider) m_provider->pause(); }
void MediaPlayerViewModel::next()      { if (m_provider) m_provider->next(); }
void MediaPlayerViewModel::previous()  { if (m_provider) m_provider->previous(); }

void MediaPlayerViewModel::togglePlayPause()
{
    if (m_isPlaying) pause(); else play();
}

void MediaPlayerViewModel::seek(double progress)
{
    if (m_provider && m_track.durationMs > 0) {
        qint64 pos = static_cast<qint64>(progress * m_track.durationMs);
        m_provider->seek(pos);
    }
}

void MediaPlayerViewModel::setVolume(float volume)
{
    if (m_provider) m_provider->setVolume(volume);
}

void MediaPlayerViewModel::onTrackChanged(const hmi::TrackInfo &track)
{
    m_track = track;
    emit trackChanged();
}

void MediaPlayerViewModel::onPositionChanged(qint64 positionMs)
{
    m_position = positionMs;
    emit positionChanged();
}

void MediaPlayerViewModel::onPlaybackStateChanged(hmi::PlaybackState state)
{
    m_isPlaying = (state == PlaybackState::Playing);
    emit playbackStateChanged();
}

void MediaPlayerViewModel::onVolumeChanged(float volume)
{
    m_volume = volume;
    emit volumeChanged();
}

QString MediaPlayerViewModel::formatTime(qint64 ms)
{
    int totalSec = static_cast<int>(ms / 1000);
    int min = totalSec / 60;
    int sec = totalSec % 60;
    return QStringLiteral("%1:%2").arg(min).arg(sec, 2, 10, QLatin1Char('0'));
}

} // namespace hmi
