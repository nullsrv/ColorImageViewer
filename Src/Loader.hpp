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

#include <QDir>
#include <QString>
#include <QGraphicsScene>
#include <QList>

namespace ColorImageViewer {

class Loader
{
    QDir            mDirectory;
    QGraphicsScene* mScenePtr;
    QList<Image*>   mImageList;

    auto CalculateAvarageColor (const QImage* image) -> QColor;

public:
    Loader  ();
    ~Loader ();

    auto load (QString directory, QGraphicsScene* scene) -> bool;
};

} // namespace ColorImageViewer
