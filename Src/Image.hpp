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

#include <QColor>
#include <QDateTime>
#include <QImage>
#include <QString>
#include <QFileInfo>

namespace ColorImageViewer {

class Image
{
    friend class ImageLoader;

    // Image information.
    int        mWidth         = 0;            // original image width
    int        mHeight        = 0;            // original image height
    QString    mPath          = "";           // full path
    size_t     mSize          = 0;            // size in bytes
    QDateTime  mLastModified  = QDateTime();
    QColor     mAverageColor  = QColor();
    
    // Draw data.
    bool       mIsLoaded      = false;
    QByteArray mCompressed    = QByteArray(); // original image compressed in jpg
    QImage*    mImage         = nullptr;
    QImage*    mThumbnail     = nullptr;      // always avalible, tile of size [ImageItem x ImageItem]

    Image (const QFileInfo file, const QImage* image)
    {
        mSize         = file.size();
        mLastModified = file.lastModified();

        mThumbnail    = new QImage(image->scaled(64, 64, Qt::AspectRatioMode::KeepAspectRatio));
        mImage        = mThumbnail;
        mIsLoaded     = true;
    }

public:
    ~Image ()
    {
    }

    auto image     () const -> QImage* { return mImage; }
    auto thumbnail () const -> QImage* { return mThumbnail; }

    auto width  () const -> int { return mWidth; }
    auto height () const -> int { return mHeight; }

    auto averageColor () const -> QColor { return mAverageColor; }
    auto averageColor (QColor color) -> void { mAverageColor = color; }
};

} // namespace ColorImageViewer
