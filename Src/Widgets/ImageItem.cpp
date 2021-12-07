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

#include "ImageItem.hpp"
#include "ImageGrid.hpp"
#include "Common/Scaler.hpp"

#include <QGraphicsScene>

namespace ColorImageViewer {

ImageItem::ImageItem (Image* image)
    : mImage (image)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);

    // Scale the size to fit in item box.
    const auto scaledSize = Scaler::scaleWithRatio(image->width(), image->height(), 64, 64);
    mItemWidth  = scaledSize.width();
    mItemHeight = scaledSize.height();

    const auto halfWidth  = mItemWidth / 2;
    const auto halfHeight = mItemHeight / 2;

    mTopLeft     = QPoint(-halfWidth, -halfHeight);
    mBottomRight = QPoint(halfWidth, halfHeight);
}

ImageItem::~ImageItem()
{
}

auto ImageItem::boundingRect () const -> QRectF
{
    return QRectF(mTopLeft.x(), mTopLeft.y(), mItemWidth, mItemHeight);
}

auto ImageItem::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) -> void
{
    const auto lod = option->levelOfDetailFromTransform(painter->worldTransform());

    auto overlay = false;
    auto color   = QColor();
    
    auto view = static_cast<ImageGrid*>(scene()->views().first());
    if (!view->IsPanActive())
    {
        if (option->state & QStyle::State_MouseOver)
        {
            color = QColor(Qt::GlobalColor::black);
            overlay = true;
        }
        if (option->state & QStyle::State_Selected)
        {
            color = QColor(Qt::GlobalColor::red);
            overlay = true;
        }
    }

    if (lod < 1.0)
    {
        painter->fillRect(QRectF(mTopLeft, mBottomRight), mImage->averageColor());
    }
    else if (lod < 2.0)
    {
        if (const auto img = mImage->thumbnail())
        {
            painter->drawImage(QRectF(mTopLeft, mBottomRight), *img);
        }
    }
    else
    {
        if (const auto img = mImage->image())
        {
            painter->drawImage(QRectF(mTopLeft, mBottomRight), *img);
        }
    }

    if (overlay)
    {
        const auto maskColor = QColor(255, 255, 255, 32);
        const auto x0 = mTopLeft.x();
        const auto y0 = mTopLeft.y();
        const auto x1 = mBottomRight.x();
        const auto y1 = mBottomRight.y();

        const auto points = QList<QPoint>({
            QPoint(x0, y0),
            QPoint(x1, y0),
            QPoint(x1, y1),
            QPoint(x0, y1),
        });

        painter->setPen(QPen(color, 1));
        painter->drawPolygon(points.data(), points.size());

        painter->fillRect(x0, y0, mItemWidth, mItemHeight, maskColor);
    }
}

auto ImageItem::mousePressEvent (QGraphicsSceneMouseEvent* e) -> void
{
    update();
    QGraphicsItem::mousePressEvent(e);
}

auto ImageItem::mouseMoveEvent (QGraphicsSceneMouseEvent* e) -> void
{
    update();
    QGraphicsItem::mouseMoveEvent(e);
}

auto ImageItem::mouseReleaseEvent (QGraphicsSceneMouseEvent* e) -> void
{
    update();
    QGraphicsItem::mouseReleaseEvent(e);
}

auto ImageItem::mouseDoubleClickEvent (QGraphicsSceneMouseEvent* e) -> void
{
    QGraphicsItem::mouseDoubleClickEvent(e);
}

} // namespace ColorImageViewer
