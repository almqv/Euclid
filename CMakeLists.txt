cmake_minimum_required(VERSION 3.24.2)

project(Euclid VERSION 1.0)

#### Sources
file(GLOB HEADERS headers/*.hpp headers/*.h)
file(GLOB SOURCES src/*.cpp src/*.c)

add_executable(Euclid src/main.cpp)

include_directories(headers)
target_sources(Euclid PRIVATE ${SOURCES})

#### Libs
# GLFW 
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

# GLAD
add_subdirectory(lib/glad)

# GLM
add_subdirectory(lib/glm)

#### External headers & sources
file(GLOB EXTERN_SOURCES extern/*)
include_directories(${EXTERN_SOURCES})
link_directories(${EXTERN_SOURCES})

#### Linking
target_link_libraries(Euclid PRIVATE glfw glad glm)
