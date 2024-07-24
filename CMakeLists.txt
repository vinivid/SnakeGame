cmake_minimum_required(VERSION 3.5)
project(SnakeGame VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libraries/glfw-3.4)
add_subdirectory(libraries/control)
add_subdirectory(libraries/camera)
add_subdirectory(libraries/glad)

add_executable(Snake
    main.cpp
)

target_include_directories(Snake PRIVATE headers)
target_link_libraries(Snake Glad)
target_link_libraries(Snake camera)
target_link_libraries(Snake control)
target_link_libraries(Snake OpenGL::GL)
target_link_libraries(Snake glfw)