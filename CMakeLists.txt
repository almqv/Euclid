cmake_minimum_required(VERSION 3.24.2)

project(Hohmann VERSION 1.0)

set(SOURCES src/main.cpp)
add_executable(Hohmann ${SOURCES})

# Includes
set(LIB_INCLUDE_DIRS include/glad/ include/GLFW/ include/KHR/)
include_directories(${LIB_INCLUDE_DIRS})

# GLFW submodule
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)

# GLAD
add_subdirectory(lib/glad)

# Linking
target_link_libraries(Hohmann PRIVATE glfw glad)
