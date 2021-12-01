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

#include "Image.hpp"

namespace ColorImageViewer {

Image::Image (QFileInfo file)
{
    auto image = new QImage(file.filePath());
    auto scaled = new QImage(image->scaled(128, 128, Qt::AspectRatioMode::KeepAspectRatio));

    mImage = scaled;
    if (mImage)
    {
        mWidth        = image->width();  // save original width
        mHeight       = image->height(); // save original height
        mSize         = file.size();
        mLastModified = file.lastModified();
        mThumbnail    = new QImage(mImage->scaled(32, 32, Qt::AspectRatioMode::KeepAspectRatio));
        mIsLoaded     = true;
    }

    delete image;
}
    
Image::~Image ()
{
    if (mThumbnail)
    {
        delete mThumbnail;
    }

    if (mImage)
    {
        delete mImage;
    }
}

} // namespace ColorImageViewer
