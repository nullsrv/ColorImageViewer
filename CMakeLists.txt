cmake_minimum_required(VERSION 3.10)

project(ColorImageViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Looking for Qt6...")
find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
if (${Qt6_FOUND})
    message("Found Qt " ${Qt6_VERSION})
else()
    message("Couldn't find Qt")
endif()

set(PROJECT_SOURCES
        Src/Main.cpp
        Src/MainWindow.cpp
        Src/MainWindow.hpp
        Src/MainWindow.ui
        Src/ImageGrid.hpp
        Src/ImageGrid.cpp
        Src/ImageItem.hpp
        Src/ImageItem.cpp
        Src/Loader.hpp
        Src/Loader.cpp
)

qt_add_executable(${CMAKE_PROJECT_NAME}
    MANUAL_FINALIZATION
    WIN32
    ${PROJECT_SOURCES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${CMAKE_PROJECT_NAME})
endif()
