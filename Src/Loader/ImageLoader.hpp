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

#include "Common/AverageColor.hpp"
#include "Common/Image.hpp"
#include "Common/Scaler.hpp"

#include <QBuffer>
#include <QByteArray>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QFileInfo>

namespace ColorImageViewer {

class ImageLoader
{
public:
    static auto load (const QFileInfo& path) -> Image*
    {
        auto reader = QImageReader();
        reader.setFileName(path.filePath());

        // Get original image size and calculate scaled width and height.
        const auto originalSize = reader.size();
        reader.setScaledSize(
            Scaler::scaleWithRatio(originalSize.width(), originalSize.height(), 1024, 1024)
        );
        
        // Read the image.
        auto image = reader.read();
        if (image.isNull())
        {
            return nullptr;
        }

        // Create scaled version compressed in jpg.
        auto bytes  = QByteArray();
        auto buffer = QBuffer(&bytes);
        auto writer = QImageWriter(&buffer, "jpg");

        writer.write(image);

        // Calculate average color.
        auto avgColor = CalculateAverageColor(&image);

        // Create Image and save original details.
        auto out = new Image(path, &image);
        out->mWidth  = originalSize.width();
        out->mHeight = originalSize.height();


        return out;
    }
};

} // namespace ColorImageViewer
