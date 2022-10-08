cmake_minimum_required(VERSION 3.24.2)

project(Hohmann VERSION 1.0)

set(SOURCES src/main.cpp)
add_executable(Hohmann ${SOURCES})

# GLFW submodule
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
target_link_libraries(Hohmann glfw)
