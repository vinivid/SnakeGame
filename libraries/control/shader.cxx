/* Made by ViniVid
   https://github.com/vinivid/SnakeGame
   Contact: frato.vini@gmail.com
   This was made with basis on the 'LearOpenGl' tutorial at https://learnopengl.com/
   And also this
   https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions?tab=CC0-1.0-1-ov-file
*/

#include <glad/glad.h>

#include "shaders.hpp"
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream v_shader_file;
    std::ifstream f_shader_file;

    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        v_shader_file.open(vertexPath);
        f_shader_file.open(fragmentPath);
        std::stringstream v_shader_stream, f_shader_stream;

        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();

        v_shader_file.close();
        f_shader_file.close();

        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str(); 
    }catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
    }

    const char* v_shader_source = vertex_code.c_str();
    const char* f_shader_source = fragment_code.c_str();

    unsigned int vertex;
    vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex, 1, &v_shader_source, NULL);
    glCompileShader(vertex);

    int state_compile;
    int size_of_error;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &state_compile);

    if(!(state_compile)){
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &size_of_error);
        char* info_log = new char[size_of_error];
        glGetShaderInfoLog(vertex, size_of_error, NULL, info_log);

        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << "\n";

        delete[] info_log;
    }

    unsigned int fragment;
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment ,1, &f_shader_source, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &state_compile);

    if(!(state_compile)){
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size_of_error);
        char* info_log = new char[size_of_error];
        glGetShaderInfoLog(fragment, size_of_error, NULL, info_log);

        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << "\n";

        delete[] info_log;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &state_compile);

    if(!state_compile){
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &size_of_error);
        char* info_log = new char[size_of_error];
        glGetShaderInfoLog(ID, size_of_error, NULL, info_log);

        std::cout << "ERROR::PROGRAM::LINK::FAILED\n" << info_log << "\n";

        delete[] info_log;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    get_all_uniforms();
}

void Shader::use() const noexcept{
    glUseProgram(ID);
}

void Shader::update_shader(const char* uniform, float *val){
    glProgramUniformMatrix4fv(ID, unifroms[uniform].location, unifroms[uniform].count, GL_FALSE, val);
}

void Shader::update_shader(const char* uniform, int val){
    glProgramUniform1i(ID, unifroms[uniform].location, val);
}


/*Why use this function instead of using the uniforms names by hand and setting multiple functions for them
is that the map will automatically throw if you are selecting a wrong uniform and we can
overload the funciton.

It also is quicker because we don't have to keep asking openGL for uniform characteristics
*/
void Shader::get_all_uniforms(){
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &uniform_qtt);

    if(uniform_qtt){
        GLint max_name_len = 0;
        GLsizei length = 0;
        GLsizei count = 0;
        GLenum type = GL_NONE;
        glGetProgramiv(ID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_len);

        auto uniform_name = std::make_unique<char[]>(max_name_len);

        for(GLint i = 0; i < uniform_qtt; ++i){
            glGetActiveUniform(ID, i, max_name_len, &length, &count, &type, uniform_name.get());

            uniform_info tmp;
            tmp.location = glGetUniformLocation(ID, uniform_name.get());
            tmp.count = count;

            unifroms.emplace(std::make_pair(std::string(uniform_name.get(), length), tmp));
        }
    }
}