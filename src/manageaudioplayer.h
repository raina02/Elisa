/*
 * Copyright 2016 Matthieu Gallien <matthieu_gallien@yahoo.fr>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MANAGEAUDIOPLAYER_H
#define MANAGEAUDIOPLAYER_H

#include "elisaLib_export.h"

#include <QObject>
#include <QPersistentModelIndex>
#include <QAbstractItemModel>
#include <QUrl>
#include <QMediaPlayer>

class QDateTime;

class ELISALIB_EXPORT ManageAudioPlayer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QPersistentModelIndex currentTrack
               READ currentTrack
               WRITE setCurrentTrack
               NOTIFY currentTrackChanged)

    Q_PROPERTY(QAbstractItemModel* playListModel
               READ playListModel
               WRITE setPlayListModel
               NOTIFY playListModelChanged)

    Q_PROPERTY(QUrl playerSource
               READ playerSource
               NOTIFY playerSourceChanged)

    Q_PROPERTY(int titleRole
               READ titleRole
               WRITE setTitleRole
               NOTIFY titleRoleChanged)

    Q_PROPERTY(int artistNameRole
               READ artistNameRole
               WRITE setArtistNameRole
               NOTIFY artistNameRoleChanged)

    Q_PROPERTY(int albumNameRole
               READ albumNameRole
               WRITE setAlbumNameRole
               NOTIFY albumNameRoleChanged)

    Q_PROPERTY(int urlRole
               READ urlRole
               WRITE setUrlRole
               NOTIFY urlRoleChanged)

    Q_PROPERTY(int isPlayingRole
               READ isPlayingRole
               WRITE setIsPlayingRole
               NOTIFY isPlayingRoleChanged)

    Q_PROPERTY(QMediaPlayer::MediaStatus playerStatus
               READ playerStatus
               WRITE setPlayerStatus
               NOTIFY playerStatusChanged)

    Q_PROPERTY(QMediaPlayer::State playerPlaybackState
               READ playerPlaybackState
               WRITE setPlayerPlaybackState
               NOTIFY playerPlaybackStateChanged)

    Q_PROPERTY(QMediaPlayer::Error playerError
               READ playerError
               WRITE setPlayerError
               NOTIFY playerErrorChanged)

    Q_PROPERTY(qint64 audioDuration
               READ audioDuration
               WRITE setAudioDuration
               NOTIFY audioDurationChanged)

    Q_PROPERTY(bool playerIsSeekable
               READ playerIsSeekable
               WRITE setPlayerIsSeekable
               NOTIFY playerIsSeekableChanged)

    Q_PROPERTY(qint64 playerPosition
               READ playerPosition
               WRITE setPlayerPosition
               NOTIFY playerPositionChanged)

    Q_PROPERTY(qint64 playControlPosition
               READ playControlPosition
               WRITE setPlayControlPosition
               NOTIFY playControlPositionChanged)

    Q_PROPERTY(QVariantMap persistentState
               READ persistentState
               WRITE setPersistentState
               NOTIFY persistentStateChanged)

public:

    explicit ManageAudioPlayer(QObject *parent = nullptr);

    QPersistentModelIndex currentTrack() const;

    QAbstractItemModel* playListModel() const;

    int urlRole() const;

    int isPlayingRole() const;

    QUrl playerSource() const;

    QMediaPlayer::MediaStatus playerStatus() const;

    QMediaPlayer::State playerPlaybackState() const;

    QMediaPlayer::Error playerError() const;

    qint64 audioDuration() const;

    bool playerIsSeekable() const;

    qint64 playerPosition() const;

    qint64 playControlPosition() const;

    QVariantMap persistentState() const;

    int playListPosition() const;

    int titleRole() const;

    int artistNameRole() const;

    int albumNameRole() const;

Q_SIGNALS:

    void currentTrackChanged();

    void playListModelChanged();

    void playerSourceChanged(QUrl url);

    void urlRoleChanged();

    void isPlayingRoleChanged();

    void playerStatusChanged();

    void playerPlaybackStateChanged();

    void playerErrorChanged();

    void playerPlay();

    void playerPause();

    void playerStop();

    void skipNextTrack();

    void audioDurationChanged();

    void playerIsSeekableChanged();

    void playerPositionChanged();

    void playControlPositionChanged();

    void persistentStateChanged();

    void seek(qint64 position);

    void saveUndoPositionInAudioWrapper(qint64 position);

    void restoreUndoPositionInAudioWrapper();

    void titleRoleChanged();

    void artistNameRoleChanged();

    void albumNameRoleChanged();

    void sourceInError(QUrl source, QMediaPlayer::Error playerError);

    void displayTrackError(const QString &fileName);

    void startedPlayingTrack(const QUrl &fileName, const QDateTime &time);

    void currentPlayingForRadiosChanged(const QVariant &value, int role);

public Q_SLOTS:

    void setCurrentTrack(const QPersistentModelIndex &currentTrack);

    void saveForUndoClearPlaylist();

    void restoreForUndoClearPlaylist();

    void setPlayListModel(QAbstractItemModel* aPlayListModel);

    void setUrlRole(int value);

    void setIsPlayingRole(int value);

    void setPlayerStatus(QMediaPlayer::MediaStatus playerStatus);

    void setPlayerPlaybackState(QMediaPlayer::State playerPlaybackState);

    void setPlayerError(QMediaPlayer::Error playerError);

    void ensurePause();

    void ensurePlay();

    void playPause();

    void stop();

    void setAudioDuration(qint64 audioDuration);

    void setPlayerIsSeekable(bool playerIsSeekable);

    void setPlayerPosition(qint64 playerPosition);

    void setCurrentPlayingForRadios(QString title, QString nowPlaying);

    void setPlayControlPosition(int playerPosition);

    void setPersistentState(const QVariantMap &persistentStateValue);

    void playerSeek(int position);

    void playListFinished();

    void tracksDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

    void setTitleRole(int titleRole);

    void setArtistNameRole(int artistNameRole);

    void setAlbumNameRole(int albumNameRole);

private:

    void notifyPlayerSourceProperty();

    void triggerPlay();

    void triggerPause();

    void triggerStop();

    void triggerSkipNextTrack();

    void restorePreviousState();

    QPersistentModelIndex mCurrentTrack;

    QPersistentModelIndex mOldCurrentTrack;

    QAbstractItemModel *mPlayListModel = nullptr;

    int mTitleRole = Qt::DisplayRole;

    int mArtistNameRole = Qt::DisplayRole;

    int mAlbumNameRole = Qt::DisplayRole;

    int mUrlRole = Qt::DisplayRole;

    int mIsPlayingRole = Qt::DisplayRole;

    QVariant mOldPlayerSource;

    QMediaPlayer::MediaStatus mPlayerStatus = QMediaPlayer::NoMedia;

    QMediaPlayer::State mPlayerPlaybackState = QMediaPlayer::StoppedState;

    QMediaPlayer::Error mPlayerError = QMediaPlayer::NoError;

    bool mPlayingState = false;

    bool mSkippingCurrentTrack = false;

    int mAudioDuration = 0;

    bool mPlayerIsSeekable = false;

    qint64 mPlayerPosition = 0;

    QVariantMap mPersistentState;

    bool mUndoPlayingState = false;

    qint64 mUndoPlayerPosition = 0;

};

#endif // MANAGEAUDIOPLAYER_H
