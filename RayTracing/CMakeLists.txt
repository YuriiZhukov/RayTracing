cmake_minimum_required(VERSION 3.18)

project(RayTracing LANGUAGES CXX CUDA)

set(SOURCE cpuintersection.cpp 
	imagebuilder.cpp intersectionwizard.cpp 
	main.cpp matrix3x3.cpp objloader.cpp 
	ray.cpp raytracing.cpp gpuintersection.cu)

set(HEADERS cpuintersection.h 
	imagebuilder.cpp intersectionwizard.h 
	matrix3x3.h objloader.h structs.h
	ray.h raytracing.h vector3f.h)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(CUDA 10.2 REQUIRED)

add_compile_definitions(_USE_MATH_DEFINES)

add_library(RayTracing STATIC ${SOURCE} ${HEADERS})

target_link_libraries(RayTracing Qt5::Widgets Qt5::Gui Qt5::Core)