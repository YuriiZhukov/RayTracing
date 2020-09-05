cmake_minimum_required(VERSION 3.18) 

project(Visualizator)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCE imageviewer.cpp
	linemesh.cpp main.cpp visualizator.cpp)

set(HEADERS imageviewer.h
	linemesh.h visualizator.h)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/Qt5.13.2/5.13.2/msvc2017_64/")

find_package(Qt5 COMPONENTS Widgets Core Gui 3DCore 3DInput 3DRender 3DExtras REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
    )