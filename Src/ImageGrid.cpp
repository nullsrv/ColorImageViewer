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

#include "ImageGrid.hpp"
#include "ImageItem.hpp"

#include <QScrollBar>

namespace ColorImageViewer {

ImageGrid::ImageGrid (QWidget* parent)
    : mPanActive (false)
{
    setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::MinimalViewportUpdate);
    setDragMode(QGraphicsView::DragMode::NoDrag);
    setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorUnderMouse);
    setSceneRect(-1000, -1000, 2000, 2000);
    setEnabled(true);
}

auto ImageGrid::keyPressEvent (QKeyEvent* e) -> void
{
    if (e->key() == Qt::Key::Key_Z)
    {
        ZoomIn();
    }
    else if (e->key() == Qt::Key::Key_X)
    {
        ZoomOut();
    }
    else
    {
        QGraphicsView::keyPressEvent(e);
    }
}

auto ImageGrid::mousePressEvent (QMouseEvent* e) -> void
{
    if (e->button() == Qt::MouseButton::MiddleButton)
    {
        mPanPosition = e->pos();
        mPanActive = true;
        setCursor(Qt::CursorShape::ClosedHandCursor);
    }
    else
    {
        QGraphicsView::mousePressEvent(e);
    }
}

auto ImageGrid::mouseReleaseEvent (QMouseEvent* e) -> void
{
    if (e->button() == Qt::MouseButton::MiddleButton)
    {
        mPanActive = false;        
        setCursor(Qt::CursorShape::ArrowCursor);
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(e);
    }
}

auto ImageGrid::mouseMoveEvent (QMouseEvent* e) -> void
{
    if (mPanActive)
    {
        const auto pos = e->pos();
        const auto dx  = pos.x() - mPanPosition.x();
        const auto dy  = pos.y() - mPanPosition.y();
 
        auto hsb = horizontalScrollBar();
        auto vsb = verticalScrollBar();

        hsb->setValue(hsb->value() - dx);
        vsb->setValue(vsb->value() - dy);

        mPanPosition = pos;
    }
    else
    {
        QGraphicsView::mouseMoveEvent(e);
    }
}

auto ImageGrid::wheelEvent (QWheelEvent* e) -> void
{
    if (e->modifiers() & Qt::ControlModifier)
    {
        if (e->angleDelta().y() > 0)
        {
            ZoomIn();
        }
        else
        {
            ZoomOut();
        }
    }
    else
    {
        QGraphicsView::wheelEvent(e);
    }
}

} // namespace ColorImageViewer
