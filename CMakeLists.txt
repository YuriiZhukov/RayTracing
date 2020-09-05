cmake_minimum_required(VERSION 3.18)

project(RayTracingProject)

list(APPEND CMAKE_PREFIX_PATH "C:/Qt/Qt5.13.2/5.13.2/msvc2017_64/")

add_subdirectory(RayTracing)
add_subdirectory(RayTracingGui)
add_subdirectory(Visualizator)
