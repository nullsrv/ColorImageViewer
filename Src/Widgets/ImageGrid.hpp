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

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QKeyEvent>

namespace ColorImageViewer {

class ImageGrid : public QGraphicsView
{
    Q_OBJECT

    bool   mPanActive;
    QPoint mPanPosition;
public:
    ImageGrid(QWidget* parent = nullptr);

    auto SetScene(QGraphicsScene* scene)
    {        
        setScene(scene);
    }

    auto IsPanActive () -> bool { return mPanActive; }

public slots:
    auto ZoomIn  () -> void { scale(1.25, 1.25); }
    auto ZoomOut () -> void { scale(1 / 1.25, 1 / 1.25); }

protected:
    auto keyPressEvent     (QKeyEvent* e)   -> void override;
    auto mousePressEvent   (QMouseEvent* e) -> void override;
    auto mouseReleaseEvent (QMouseEvent* e) -> void override;
    auto mouseMoveEvent    (QMouseEvent* e) -> void override;
    auto wheelEvent        (QWheelEvent* e) -> void override;
};

} // namespace ColorImageViewer
