cmake_minimum_required(VERSION 3.24.2)

project(Hohmann VERSION 1.0)
add_executable(Hohmann main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(Hohmann ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
