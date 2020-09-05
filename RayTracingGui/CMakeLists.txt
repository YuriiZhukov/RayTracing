cmake_minimum_required(VERSION 3.18) 

project(RayTracingGui LANGUAGES CXX CUDA)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCE raytracinggui.cpp main.cpp)

set(HEADERS raytracinggui.h)

add_compile_definitions(_USE_MATH_DEFINES)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/Qt5.13.2/5.13.2/msvc2017_64/")

find_package(Qt5 COMPONENTS Widgets Core Gui 3DCore 3DInput 3DRender 3DExtras REQUIRED)
find_package(CUDA 10.2 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ../Visualizator/ ../RayTracing/)

target_link_directories(${PROJECT_NAME} PRIVATE ../Visualizator/build/Debug ../RayTracing/build/Debug)

target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES})

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
	Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
	RayTracing
	Visualizator
    )