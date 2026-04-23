cmake_minimum_required(VERSION 3.10)
project(Scatter3D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(scatter
    main.cpp
    src/glad.c
    visualSpace/cloud.cpp
    visualSpace/perspective.cpp
    visualSpace/point.cpp
)

target_include_directories(scatter PRIVATE
    ${CMAKE_SOURCE_DIR}/src          # resolves glad/glad.h
    ${CMAKE_SOURCE_DIR}/src/include  # resolves KHR/khrplatform.h
)

target_link_libraries(scatter PRIVATE
    glfw
    OpenGL::GL
    dl
)