cmake_minimum_required(VERSION 3.21)
project(simple-triangle-opengl33-qt6-cpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS OpenGL Widgets OpenGLWidgets)

add_executable(app)

target_sources(app PRIVATE
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
)

target_link_libraries(app PRIVATE
    Qt6::OpenGL
    Qt6::Widgets
    Qt6::OpenGLWidgets
)
