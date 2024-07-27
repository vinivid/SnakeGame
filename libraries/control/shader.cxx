/* Made by ViniVid
   https://github.com/vinivid/SnakeGame
   Contact: frato.vini@gmail.com
   This was made with basis on the 'LearOpenGl' tutorial at https://learnopengl.com/
*/

#include <glad/glad.h>

#include "shaders.hpp"
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
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::set_bool(const std::string& name, bool value) const{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    if(loc == -1){
        std::cout << "ERROR GETTING UNIFOR LOCATION\n";
        return;
    }
    glUniform1i(loc, value);
}

void Shader::set_int(const std::string& name, int value) const{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    if(loc == -1){
        std::cout << "ERROR GETTING UNIFOR LOCATION\n";
        return;
    }
    glUniform1i(loc, value);
}

void Shader::set_float(const std::string& name, float value) const{
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    if(loc == -1){
        std::cout << "ERROR GETTING UNIFOR LOCATION\n";
        return;
    }
    glUniform1f(loc, value);
}

void Shader::set_uniform_mat4f(const std::string &name, float *addres){
    unsigned int loc = glGetUniformLocation(ID, name.c_str());
    if(loc == -1){
        std::cout << "ERROR GETTING UNIFOR LOCATION\n";
        return;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, addres);
}