cmake_minimum_required(VERSION 3.16)
project(XRayViewer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(scatter
    ModelSpace.cpp
    src/glad.c
    visualSpace/cloud.cpp
    visualSpace/perspective.cpp
    visualSpace/point.cpp
)

add_executable(parser
    Parser.cpp
)

target_include_directories(scatter PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/include 
)

target_link_libraries(scatter PRIVATE
    glfw
    OpenGL::GL
    dl
)

target_link_libraries(parser PRIVATE
    ${OpenCV_LIBS}
)