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

#include "Loader.hpp"
#include "ImageItem.hpp"

#include <QDirIterator>

namespace ColorImageViewer {

Loader::Loader ()
    : mScenePtr (nullptr)
{
}

Loader::~Loader ()
{
}

auto Loader::CalculateAvarageColor (const QImage* image) -> QColor
{
    const auto pixels = image->constBits();
    const auto step   = 4;
    const auto size   = image->sizeInBytes();

    auto red   = quint64(0);
    auto green = quint64(0);
    auto blue  = quint64(0);
    auto alpha = quint64(0);

    auto count = quint64(0);

    const auto format = image->format();
    if (format != QImage::Format::Format_RGB32)
    {
        return QColor(0, 0, 0, 0);
    }

    for (auto i = qsizetype(0); i < size; i += step)
    {
        // BGRA
        blue  += pixels[i + 0];
        green += pixels[i + 1];
        red   += pixels[i + 2];
        alpha += pixels[i + 3];

        count += 1;
    }

    const auto ra = red   / static_cast<double>(count);
    const auto ga = green / static_cast<double>(count);
    const auto ba = blue  / static_cast<double>(count);
    const auto aa = alpha / static_cast<double>(count);

    return QColor(
        std::lroundf(ra),
        std::lroundf(ga),
        std::lroundf(ba),
        std::lroundf(aa)
    );
}


auto Loader::load (QString directory, QGraphicsScene* scene) -> bool
{
    mDirectory = directory;
    mScenePtr  = scene;

    auto fileList = std::vector<QFileInfo>();

    // Get list of files.
    auto it = QDirIterator(directory, {"*.png", "*.jpg"}, QDir::Files);
    while (it.hasNext())
    {
        it.next();
        fileList.push_back(it.fileInfo());
    }

    // Load.
    auto count = 1;
    auto total = fileList.size();
    for (const auto& f : fileList)
    {
        auto image = new Image(f);
        auto avg   = CalculateAvarageColor(image->image());
        image->averageColor(avg);

        mImageList.push_back(image);

        qDebug() << "Loaded image " << f.fileName()
                 << "[" << avg.red() << avg.green() << avg.blue() << avg.alpha() << "]"
                 << "(" << count << "/" << total << ")";
        
        count += 1;
    }

    // Sort.
    auto cmp = [](Image* lhs, Image* rhs) -> bool
    {
        const auto lcolor = lhs->averageColor();
        const auto rcolor = rhs->averageColor();
        return lcolor.hue() < rcolor.hue();
    };

    std::sort(mImageList.begin(), mImageList.end(), cmp);

    for (auto& image : mImageList)
    {
        auto item = new ImageItem(image);
        mScenePtr->addItem(item);
    }

    // Position.
    const auto imageWidth  = 64;
    const auto imageHeight = 64;
    const auto padding     = 4;

    const auto itemsRowSize = (imageWidth + padding) * 16;

    auto xx = -(itemsRowSize / 2);
    auto yy = -100;

    auto i = 0;
    auto x = xx;
    auto y = yy;

    for (auto& item : mScenePtr->items())
    {
        item->setPos(x, y);
        x += imageWidth + padding;
        i += 1;

        if (i >= 16)
        {
            i = 0;
            x = xx;
            y += imageHeight + padding;
        }
    }

    return true;
}

} // namespace ColorImageViewer
