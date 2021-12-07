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

#include "Widgets/ImageGrid.hpp"
#include "Widgets/ImageItem.hpp"
#include "Loader/Loader.hpp"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace ColorImageViewer {

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* mUI;
    ImageGrid*      mImageGrid;
    QGraphicsScene* mScene;
    Loader          mLoader;
    QList<Image*>   mImages;

public:
    MainWindow  (QWidget *parent = nullptr);
    ~MainWindow ();

public slots:
    auto imageLoaded (Image* image) -> void
    {
        // Position.
        const auto imageWidth  = 64;
        const auto imageHeight = 64;
        const auto padding     = 4;

        const auto itemsRowSize = (imageWidth + padding) * 16;

        const auto xx = -(itemsRowSize / 2);
        const auto yy = -100;

        static auto i = 0;
        static auto x = xx;
        static auto y = yy;

        
        //auto ptr = new Image(image);
        mImages.push_back(image);

        auto item = new ImageItem(image);
        mScene->addItem(item);

        //for (auto& item : mScene->items())
        //{
            item->setPos(x, y);
            x += imageWidth + padding;
            i += 1;

            if (i >= 16)
            {
                i = 0;
                x = xx;
                y += imageHeight + padding;
            }
        //}
    }
};

} // namespace ColorImageViewer
