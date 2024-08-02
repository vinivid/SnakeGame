#include "gl_objects.hpp"
#include <glad/glad.h>
#include <vector>

gl_objects::gl_objects(int qtt){
    VAOs.reserve(qtt);
    VBOs.reserve(3*qtt);
    IBOs.reserve(qtt);
    VAOs.resize(qtt);
    VBOs.resize(3*qtt);
    IBOs.resize(qtt);
    glCreateVertexArrays(qtt, VAOs.data());
    glCreateBuffers(qtt*3, VBOs.data());
    glCreateBuffers(qtt, IBOs.data());
    qtt_vaos = qtt;
}

gl_objects::~gl_objects(){
    glDeleteVertexArrays(qtt_vaos, VAOs.data());
    glDeleteBuffers(qtt_vaos, VBOs.data());
    glDeleteBuffers(qtt_vaos, IBOs.data());
}

void gl_objects::config_vao(int index) noexcept{
    glVertexArrayVertexBuffer(VAOs[index], 0, VBOs[vertex_vbo + 3*index], 0, 3*sizeof(float));
    glVertexArrayVertexBuffer(VAOs[index], 1, VBOs[normal_vbo + 3*index], 0, 3*sizeof(float)); 
    glVertexArrayVertexBuffer(VAOs[index], 2, VBOs[texture_vbo + 3*index], 0, 3*sizeof(float));
    glVertexArrayElementBuffer(VAOs[index], IBOs[index]);

    glEnableVertexArrayAttrib(VAOs[index], 0);
    glEnableVertexArrayAttrib(VAOs[index], 1);
    glEnableVertexArrayAttrib(VAOs[index], 2);

    glVertexArrayAttribFormat(VAOs[index], 0, 3, GL_FLOAT, GL_FALSE, static_cast<GLuint>(3*sizeof(float)));
    glVertexArrayAttribFormat(VAOs[index], 1, 3, GL_FLOAT, GL_FALSE, static_cast<GLuint>(3*sizeof(float)));
    glVertexArrayAttribFormat(VAOs[index], 2, 2, GL_FLOAT, GL_FALSE, static_cast<GLuint>(3*sizeof(float)));

    glVertexArrayAttribBinding(VAOs[index], 0,0);
    glVertexArrayAttribBinding(VAOs[index], 1,1);
    glVertexArrayAttribBinding(VAOs[index], 2,2);
}

void gl_objects::config_vbo(int index, const vertex &vt) noexcept{
    glNamedBufferData(VBOs[vertex_vbo+ 3*index], vt.pos.size()*sizeof(float), vt.pos.data(), GL_STATIC_DRAW);
    glNamedBufferData(VBOs[normal_vbo+ 3*index], vt.normal.size()*sizeof(float), vt.normal.data(), GL_STATIC_DRAW);
    glNamedBufferData(VBOs[texture_vbo+ 3*index], vt.texture.size()*sizeof(float), vt.texture.data(), GL_STATIC_DRAW);
}

void gl_objects::bind_vao(int index) const noexcept{
    glBindVertexArray(VAOs[index]);
}

void gl_objects::unbind_vao() const noexcept{
    glBindVertexArray(0);
}

void gl_objects::config_ibo(int index, const indexes_obj &id) noexcept{
    glNamedBufferData(IBOs[index], id.size()*sizeof(float), id.data(), GL_STATIC_DRAW);
}