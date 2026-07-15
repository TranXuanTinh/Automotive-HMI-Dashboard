#ifndef VIEWMODELS_MEDIAPLAYERVIEWMODEL_H
#define VIEWMODELS_MEDIAPLAYERVIEWMODEL_H

#include <QObject>

#include <core/MediaData.h>

namespace hmi {

class IMediaProvider;

class MediaPlayerViewModel : public QObject
{
    Q_OBJECT


    Q_PROPERTY(QString title READ title NOTIFY trackChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY trackChanged)
    Q_PROPERTY(QString album READ album NOTIFY trackChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY trackChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(double progress READ progress NOTIFY positionChanged)
    Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY playbackStateChanged)
    Q_PROPERTY(float volume READ volume NOTIFY volumeChanged)
    Q_PROPERTY(QString durationText READ durationText NOTIFY trackChanged)
    Q_PROPERTY(QString positionText READ positionText NOTIFY positionChanged)

public:
    explicit MediaPlayerViewModel(QObject *parent = nullptr);

    void setProvider(IMediaProvider *provider);

    QString title() const { return m_track.title; }
    QString artist() const { return m_track.artist; }
    QString album() const { return m_track.album; }
    qint64 duration() const { return m_track.durationMs; }
    qint64 position() const { return m_position; }
    double progress() const;
    bool isPlaying() const { return m_isPlaying; }
    float volume() const { return m_volume; }
    QString durationText() const;
    QString positionText() const;

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void togglePlayPause();
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void seek(double progress);
    Q_INVOKABLE void setVolume(float volume);

signals:
    void trackChanged();
    void positionChanged();
    void playbackStateChanged();
    void volumeChanged();

private slots:
    void onTrackChanged(const hmi::TrackInfo &track);
    void onPositionChanged(qint64 positionMs);
    void onPlaybackStateChanged(hmi::PlaybackState state);
    void onVolumeChanged(float volume);

private:
    static QString formatTime(qint64 ms);

    IMediaProvider *m_provider = nullptr;
    TrackInfo       m_track;
    qint64          m_position = 0;
    bool            m_isPlaying = false;
    float           m_volume = 0.7f;
};

} // namespace hmi

#endif // VIEWMODELS_MEDIAPLAYERVIEWMODEL_H
