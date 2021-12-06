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
#include "LoaderWorker.hpp"

#include <spdlog/spdlog.h>

#include <QDir>
#include <QString>

namespace ColorImageViewer {

class Loader : public QObject
{
    Q_OBJECT

private:
    QThread mWorkerThread;

public:
    Loader ()
    {
        auto worker = new LoaderWorker();
        connect(&mWorkerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Loader::startLoading, worker, &LoaderWorker::load);
        connect(worker, &LoaderWorker::imageLoaded, this, &Loader::handleImageLoaded);

        worker->moveToThread(&mWorkerThread);
        mWorkerThread.start();
    }

    ~Loader ()
    {
        mWorkerThread.quit();
        mWorkerThread.wait();
    }

    auto load (const QString& directory) -> void
    {
        spdlog::info("Loading directory '{}'", directory.toStdString());
        startLoading(directory);
    }

private slots:
    void handleImageLoaded (Image* image)
    {
        emit imageLoaded(image);
    }

signals:
    auto startLoading (const QString &) -> void;
    auto imageLoaded  (Image* image)    -> void;
};

} // namespace ColorImageViewer
