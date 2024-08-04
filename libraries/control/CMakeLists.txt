add_library(control
    control.cxx 
    shader.cxx
    gl_objects.cxx
    textures.cxx
    )

target_include_directories(control PRIVATE "${PROJECT_SOURCE_DIR}/headers")
target_link_libraries(control PRIVATE Glad)
target_link_libraries(control PRIVATE stb)