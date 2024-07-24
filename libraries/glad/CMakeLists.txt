add_library(Glad glad.c)

target_include_directories(Glad PRIVATE "${PROJECT_SOURCE_DIR}/headers")