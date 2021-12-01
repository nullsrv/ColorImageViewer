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

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QStyleOptionGraphicsItem>
#include <QDateTime>

namespace ColorImageViewer {

struct ImageInfo
{
    int width;
    int height;

    std::string path;
    QDateTime   lastModified;
};

class ImageItem : public QGraphicsItem
{
    QImage* mImage;
    int     mItemWidth;
    int     mItemHeight;
    double  mAspectRatio;
    QPoint  mTopLeft;
    QPoint  mBottomRight;
    QColor  mAverageColor;

public:
    ImageItem  (QImage* image, QColor averageColor);
    ~ImageItem ();

    auto image        () const -> QImage* { return mImage; }
    auto averageColor () const -> QColor  { return mAverageColor; }

    auto boundingRect () const -> QRectF override;
    auto paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) -> void override;

protected:
    auto mousePressEvent       (QGraphicsSceneMouseEvent* e) -> void override;
    auto mouseMoveEvent        (QGraphicsSceneMouseEvent* e) -> void override;
    auto mouseReleaseEvent     (QGraphicsSceneMouseEvent* e) -> void override;
    auto mouseDoubleClickEvent (QGraphicsSceneMouseEvent* e) -> void override;
};

} // namespace ColorImageViewer
