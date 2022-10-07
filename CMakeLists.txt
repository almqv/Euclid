cmake_minimum_required(VERSION 3.24.2)

project(Hohmann VERSION 1.0)

set(SOURCES src/main.cpp)
add_executable(Hohmann ${SOURCES})

set(INCLUDE_DIR include)
target_include_directories(Hohmann PRIVATE ${INCLUDE_DIR})

#set(INCLUDE_HEADER_FILES include/**/*.h include/**/*.hpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries( Hohmann OpenGL::GL glfw )

