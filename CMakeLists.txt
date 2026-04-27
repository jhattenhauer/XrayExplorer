cmake_minimum_required(VERSION 3.16)
project(XRayViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(ModelSpace
    ModelSpace.cpp
    src/glad.c
    visualSpace/cloud.cpp
    visualSpace/perspective.cpp
    visualSpace/point.cpp
)


target_include_directories(ModelSpace PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/include 
)

target_link_libraries(ModelSpace PRIVATE
    ${OpenCV_LIBS}
    glfw
    OpenGL::GL
    dl
)
