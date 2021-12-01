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

#include <QGraphicsScene>

namespace ColorImageViewer {

ImageItem::ImageItem (QImage* image, QColor averageColor)   
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);

    const auto w = (double)image->width();
    const auto h = (double)image->height();
    mAspectRatio = w / h;

    auto ratio = std::min(64 / w, 64 / h);

    mItemWidth  = (int)(image->width() * ratio);
    mItemHeight = (int)(image->height() * ratio);

    const auto halfWidth  = mItemWidth / 2;
    const auto halfHeight = mItemHeight / 2;

    mTopLeft     = QPoint(-halfWidth, -halfHeight);
    mBottomRight = QPoint(halfWidth, halfHeight);

    auto scaled = image->scaled(mItemWidth * 2, mItemHeight * 2);
    mImage = new QImage(scaled);

    delete image;

    mAverageColor = averageColor;
}

ImageItem::~ImageItem()
{
    delete mImage;
}

auto ImageItem::boundingRect () const -> QRectF
{
    return QRectF(mTopLeft.x(), mTopLeft.y(), mItemWidth, mItemHeight);
}

auto ImageItem::paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) -> void
{
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

    painter->drawImage(QRectF(mTopLeft, mBottomRight), *mImage);

    if (overlay)
    {
        const auto maskColor = QColor(255, 255, 255, 32);
        const auto x0 = mTopLeft.x();
        const auto y0 = mTopLeft.y();
        const auto x1 = x0 + mItemWidth;
        const auto y1 = y0 + mItemHeight;

        painter->setPen(QPen(color, 1));
        painter->drawLine(x0, y0, x1, y0);
        painter->drawLine(x1, y0, x1, y1);
        painter->drawLine(x1, y1, x0, y1);
        painter->drawLine(x0, y1, x0, y0);

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
