add_library(snake_ctrl snake.cxx fruit.cxx)

target_include_directories(snake_ctrl PRIVATE "${PROJECT_SOURCE_DIR}/headers")
target_link_libraries(snake_ctrl glfw)
target_link_libraries(snake_ctrl Glad)