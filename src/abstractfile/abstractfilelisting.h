/*
 * Copyright 2016-2017 Matthieu Gallien <matthieu_gallien@yahoo.fr>
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

#ifndef ABSTRACTFILELISTING_H
#define ABSTRACTFILELISTING_H

#include "elisaLib_export.h"

#include <QObject>
#include <QString>
#include <QUrl>
#include <QHash>
#include <QVector>
#include <QDateTime>

#include <memory>

class AbstractFileListingPrivate;
class MusicAudioTrack;
class FileScanner;
class QFileInfo;
class QMimeDatabase;

class ELISALIB_EXPORT AbstractFileListing : public QObject
{

    Q_OBJECT

public:

    explicit AbstractFileListing(QObject *parent = nullptr);

    ~AbstractFileListing() override;

    virtual void applicationAboutToQuit();

    const QStringList& allRootPaths() const;

Q_SIGNALS:

    void tracksList(const QList<MusicAudioTrack> &tracks, const QHash<QString, QUrl> &covers);

    void removedTracksList(const QList<QUrl> &removedTracks);

    void modifyTracksList(const QList<MusicAudioTrack> &modifiedTracks, const QHash<QString, QUrl> &covers);

    void indexingStarted();

    void indexingFinished();

    void askRestoredTracks();

    void errorWatchingFileSystemChanges();

public Q_SLOTS:

    void refreshContent();

    void init();

    void newTrackFile(const MusicAudioTrack &partialTrack);

    void restoredTracks(QHash<QUrl, QDateTime> allFiles);

    void setAllRootPaths(const QStringList &allRootPaths);

    void databaseFinishedInsertingTracksList();

    void databaseFinishedRemovingTracksList();

protected Q_SLOTS:

    void directoryChanged(const QString &path);

    void fileChanged(const QString &modifiedFileName);

protected:

    virtual void executeInit(QHash<QUrl, QDateTime> allFiles);

    virtual void triggerRefreshOfContent();

    void scanDirectory(QList<MusicAudioTrack> &newFiles, const QUrl &path);

    virtual MusicAudioTrack scanOneFile(const QUrl &scanFile, const QFileInfo &scanFileInfo);

    void watchPath(const QString &pathName);

    void addFileInDirectory(const QUrl &newFile, const QUrl &directoryName);

    void scanDirectoryTree(const QString &path);

    void setHandleNewFiles(bool handleThem);

    void emitNewFiles(const QList<MusicAudioTrack> &tracks);

    void addCover(const MusicAudioTrack &newTrack);

    void removeDirectory(const QUrl &removedDirectory, QList<QUrl> &allRemovedFiles);

    void removeFile(const QUrl &oneRemovedTrack, QList<QUrl> &allRemovedFiles);

    QHash<QUrl, QDateTime>& allFiles();

    void checkFilesToRemove();

    FileScanner& fileScanner();

    bool checkEmbeddedCoverImage(const QString &localFileName);

    bool waitEndTrackRemoval() const;

    void setWaitEndTrackRemoval(bool wait);

    const QMimeDatabase& mimeDatabase() const;

private:

    std::unique_ptr<AbstractFileListingPrivate> d;

};



#endif // ABSTRACTFILELISTING_H
