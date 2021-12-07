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

#include <QSize>

namespace ColorImageViewer {

class Scaler
{
public:
    static auto scaleWithRatio (int width, int height, int maxWidth, int maxHeight) -> QSize
    {
        const auto w = static_cast<double>(width);
        const auto h = static_cast<double>(height);

        const auto ratio = std::min(maxWidth / w, maxHeight / h);

        return QSize(
            static_cast<int>(width * ratio),
            static_cast<int>(height * ratio)
        );
    }
};

} // namespace ColorImageViewer
