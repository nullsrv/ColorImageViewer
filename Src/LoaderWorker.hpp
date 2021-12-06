// ColorImageViewer
// 
// Copyright (C) 2021 serverfailure71
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
// 
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "Image.hpp"
#include "LoaderTask.hpp"

#include <QDirIterator>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QString>
#include <QThreadPool>

namespace ColorImageViewer {

class LoaderWorker : public QObject
{
    Q_OBJECT

private:
    QThreadPool            mThreadPool;
    QMap<int, LoaderTask*> mTasks;
    QMutex                 mTasksAccessMutex;
    int                    mNextTaskId;

    auto nextTaskId () -> int
    {
        return mNextTaskId++;
    }

public:
    LoaderWorker ()
        : mNextTaskId (0)
    {
        mThreadPool.setMaxThreadCount(4);
    }

public slots:
    auto load (const QString& directory) -> void
    {
        // Get list of files.
        auto total = 0;
        auto it    = QDirIterator(directory, {"*.png", "*.jpg"}, QDir::Files);

        auto tasksLockGuard = QMutexLocker(&mTasksAccessMutex);
        while (it.hasNext())
        {
            it.next();
            
            // Create new task.
            auto id   = nextTaskId();
            auto task = new LoaderTask(id, it.fileInfo());
            connect(task, &LoaderTask::loaded, this, &LoaderWorker::handleImageLoaded);
            mTasks.insert(id, task);
        }

        // Start loading.
        for (auto task : mTasks)
        {
            mThreadPool.start(task);
        }
    }

private slots:
    auto handleImageLoaded (int taskId, Image* image) -> void
    {
        {
            auto tasksLockGuard = QMutexLocker(&mTasksAccessMutex);
            mTasks.remove(taskId);
        }
        emit imageLoaded(image);
    }

signals:
    auto imageLoaded (Image* image) -> void;
};

} // namespace ColorImageViewer
