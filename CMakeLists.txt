cmake_minimum_required(VERSION 2.8.12)

project(PongAR)

add_compile_options(-std=c++11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Multimedia)
find_package(Qt5MultimediaWidgets)

qt5_wrap_ui(
    ui_files
    client.ui
)

include_directories(Externals/opencv/include)

if (UNIX)
    link_directories(Externals/opencv/libs/ubuntu16.04)
endif()

add_executable(
    PongAR
    main.cpp
    client.cpp
    client.h
    cameraframegrabber.cpp
    cameraframegrabber.h
    camerahandler.cpp
    camerahandler.h
    imageutils.h
    imageutils.cpp
    ${ui_files}
)

if (UNIX)
    target_link_libraries(
        PongAR
        libopencv_world.a
        libippiw.a
        libippicv.a
        libittnotify.a
        libIlmImf.a
        liblibwebp.a
        -lpng
        -ljpeg
        -ltiff
        -ljasper
        -lpthread
        -lz
        -ldl
    )
endif()

target_link_libraries(
    PongAR
    Qt5::Core
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::MultimediaWidgets
)