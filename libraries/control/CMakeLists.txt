add_library(control
    control.cxx 
    shader.cxx
    )

target_include_directories(control PRIVATE "${PROJECT_SOURCE_DIR}/headers")
target_link_libraries(control PRIVATE Glad)