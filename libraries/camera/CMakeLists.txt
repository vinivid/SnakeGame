add_library(camera camera.cxx)

target_include_directories(camera PRIVATE "${PROJECT_SOURCE_DIR}/headers")
target_link_libraries(camera glfw)
target_link_libraries(camera Glad)