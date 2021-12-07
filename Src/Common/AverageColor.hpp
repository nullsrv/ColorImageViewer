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

#include <QColor>
#include <QImage>

namespace ColorImageViewer {

inline auto CalculateAverageColor (const QImage* image) -> QColor
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

} // namespace ColorImageViewer
