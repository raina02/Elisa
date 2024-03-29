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

#include "localfilelisting.h"

#include "musicaudiotrack.h"

#include "abstractfile/indexercommon.h"

#include <QThread>
#include <QHash>
#include <QFileInfo>
#include <QDir>
#include <QFileSystemWatcher>
#include <QMimeDatabase>
#include <QStandardPaths>

#include <QDebug>

#include <algorithm>

class LocalFileListingPrivate
{
public:

};

LocalFileListing::LocalFileListing(QObject *parent) : AbstractFileListing(parent), d(std::make_unique<LocalFileListingPrivate>())
{
}

LocalFileListing::~LocalFileListing()
= default;

void LocalFileListing::executeInit(QHash<QUrl, QDateTime> allFiles)
{
    qCDebug(orgKdeElisaIndexer()) << "LocalFileListing::executeInit" << "with" << allFiles.size() << "files";
    AbstractFileListing::executeInit(std::move(allFiles));
}

void LocalFileListing::triggerRefreshOfContent()
{
    Q_EMIT indexingStarted();

    qCDebug(orgKdeElisaIndexer()) << "LocalFileListing::triggerRefreshOfContent" << allRootPaths();

    AbstractFileListing::triggerRefreshOfContent();

    const auto &rootPaths = allRootPaths();
    for (const auto &onePath : rootPaths) {
        scanDirectoryTree(onePath);
    }

    setWaitEndTrackRemoval(false);

    checkFilesToRemove();

    if (!waitEndTrackRemoval()) {
        Q_EMIT indexingFinished();
    }
}


#include "moc_localfilelisting.cpp"
