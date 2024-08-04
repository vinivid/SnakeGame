#pragma once
#include <glad/glad.h>
#include <unordered_map>
#include <string>
struct uniform_info{
    GLint location;
    GLsizei count; 
};

class Shader{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);

        unsigned int ID;
        std::unordered_map<std::string, uniform_info> unifroms;

        //Uses the shader program associated with the class
        void use() const noexcept;
        void update_shader(const char* uniform, float *val);
        void update_shader(const char* uniform, int val);
    private:
        /*This function gets all of the uniforms in the shader and puts them in a
        map of all the uniforms, it basic becomes a validator
        */
        void get_all_uniforms();
        GLint uniform_qtt = 0;
};