cmake_minimum_required(VERSION 3.10)
project(Scatter3D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

find_package(GLUT REQUIRED)

add_executable(scatter main.cpp)

target_include_directories(scatter PRIVATE ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(scatter PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})