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

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

namespace ColorImageViewer {

inline auto init_logger () -> void
{
    auto logger = spdlog::basic_logger_mt("file_logger", "ColorImageViewer.log", true);
    logger->set_pattern("[%Y-%m-%d %T.%e][%8l]{%5t} %v");

    spdlog::flush_on(spdlog::level::info);
    spdlog::set_level(spdlog::level::level_enum::info);

#if defined(_DEBUG) && defined(_WIN32)
    auto vsdbgsink = std::make_shared<spdlog::sinks::windebug_sink_mt>();
    vsdbgsink->set_pattern("[%8l]{%5t} %v");
    logger->sinks().push_back(vsdbgsink);

    spdlog::flush_on(spdlog::level::debug);
    spdlog::set_level(spdlog::level::level_enum::debug);
#endif

    spdlog::set_default_logger(logger);
}

} // namespace ColorImageViewer
