cmake_minimum_required(VERSION 3.16)

project(Pawche VERSION 1.4 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(Pawche
    main.cpp
    animal.h
    animal.cpp
    mainwindow.ui
)

target_link_libraries(Pawche PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(Pawche PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Pawche PROPERTIES WIN32_EXECUTABLE TRUE)
