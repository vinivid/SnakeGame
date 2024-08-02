add_library(stb stbimplem.cxx)

target_include_directories(stb PRIVATE "${PROJECT_SOURCE_DIR}/headers")