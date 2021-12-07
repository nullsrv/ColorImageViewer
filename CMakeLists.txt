cmake_minimum_required(VERSION 3.10)

project(ColorImageViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

message("Looking for Qt6...")
find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
if (${Qt6_FOUND})
    message("Found Qt " ${Qt6_VERSION})
else()
    message("Couldn't find Qt")
endif()

set(PROJECT_SOURCES
        Src/Common/AverageColor.hpp
        Src/Common/Image.hpp
        Src/Common/Scaler.hpp
        
        Src/Widgets/ImageGrid.cpp
        Src/Widgets/ImageGrid.hpp
        Src/Widgets/ImageItem.cpp
        Src/Widgets/ImageItem.hpp

        Src/Windows/MainWindow.cpp
        Src/Windows/MainWindow.hpp
        Src/Windows/MainWindow.ui
        
        Src/Loader/Loader.hpp
        Src/Loader/LoaderTask.hpp
        Src/Loader/LoaderWorker.hpp
        Src/Loader/ImageLoader.hpp

        Src/Logger.hpp
        Src/Main.cpp
)

qt_add_executable(${CMAKE_PROJECT_NAME}
    MANUAL_FINALIZATION
    WIN32
    ${PROJECT_SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "Src")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "Deps/spdlog/include")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${CMAKE_PROJECT_NAME})
endif()
