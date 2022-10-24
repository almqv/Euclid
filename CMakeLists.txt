cmake_minimum_required(VERSION 3.24.2)

project(Hohmann VERSION 1.0)

#### Sources
file(GLOB SOURCES src/*.cpp headers/*.hpp)
add_executable(Hohmann ${SOURCES})


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
target_link_libraries(Hohmann PRIVATE glfw glad glm)
