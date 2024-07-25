#pragma once

#include <string>

class Shader{
    private:

    public:
        //The id the program is going to receive
        unsigned int ID;   

        /*The constructor of the shader object which will read from the shader files
        and then compile both of the shader into a single program to be utilized

        Argument 1: It is the path to the vertex shader
        Argument 2: It is the path to the fragment shader
        */
        Shader(const char* vertexPath, const char* fragmentPath);

        //Use the shader program
        void use();

        //Set a boolean value to a uniform
        void set_bool(const std::string &name, bool value) const;

        //Set a int value to a uniform
        void set_int(const std::string &name, int value) const;
        //Set a float value to a uniform   
        void set_float(const std::string &name, float value) const;
        //Set uniform shader to a 4 by 4 matrix
        void set_uniform_mat4f(const std::string &name, float *addres);
};