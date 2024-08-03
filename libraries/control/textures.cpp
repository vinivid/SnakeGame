#include "textures.hpp"
#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"

gl_tex::gl_tex(int qtt){
    texx.reserve(qtt);
    texx.resize(qtt);
    glCreateTextures(GL_TEXTURE_2D, qtt, texx.data());
    qtt_tex = qtt;
}

gl_tex::~gl_tex(){
    glDeleteTextures(qtt_tex, texx.data());
}

void gl_tex::put_texture(int index, const char *file){
   stbi_set_flip_vertically_on_load(true);
   int width = 0; int height = 0; int channels = 0;

    unsigned char *image_data = stbi_load(file, &width, &height, &channels, 0);

    if(!image_data){
        std::cout << "\n\nERROR: COULDNT LOAD IMAGE\n\n";
    }

    glTextureParameteri(texx[index], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texx[index], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(texx[index], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texx[index], GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureStorage2D(texx[index], 1, GL_RGBA8, width, height);
    glTextureSubImage2D(texx[index], 0,0,0, width, height, GL_RGB, GL_UNSIGNED_BYTE, image_data);

    glBindTextureUnit(index, texx[index]);
    stbi_image_free(image_data);
}

void gl_tex::unbind_texture(int index){
    glBindTextureUnit(index, 0);
}