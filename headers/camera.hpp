#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera{
    private:
        glm::vec3 look_vector;
        glm::vec3 up;
        glm::vec3 pos;
        glm::mat4 translate_matrix;
        glm::mat4 view_matrix;
        double last_mouse_pos_x = 0;
        double last_mouse_pos_y = 0;
        double delta_pos_x = 0;
        double delta_pos_y = 0;
        float speed = 0.1f;
    public:
        Camera();

        void read_keyboard(GLFWwindow* window);
        void read_mouse(GLFWwindow* window);
        void set_speed(float a);

        glm::mat4& get_translate();
        glm::mat4& get_view_matrix();
};