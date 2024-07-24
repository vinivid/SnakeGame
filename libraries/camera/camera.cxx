#include "glad/glad.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include "camera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <iostream>

Camera::Camera(){
    up.x = 0; up.y = 1; up.z = 0;
    pos.x = 0; pos.y = 0; pos.z = 0;
    look_vector.x = 0; look_vector.y = 0; look_vector.z = 1;
}

void Camera::read_keyboard(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        pos += (look_vector * speed);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        pos += glm::cross(up, look_vector) * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        pos -= (look_vector * speed);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        pos -= glm::cross(up, look_vector) *speed;
    }
}

void Camera::read_mouse(GLFWwindow* window){
    double xpos;
    double ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    delta_pos_x = last_mouse_pos_x - xpos;
    delta_pos_y = (ypos - last_mouse_pos_y)/5.0f;
    last_mouse_pos_y = ypos;
    std::cout << "last pos y: " << last_mouse_pos_y << "\n";
    std::cout << "delta pos y: " << delta_pos_y << "\n";
    last_mouse_pos_x = xpos;
}

void Camera::set_speed(float a){
    speed = a;
}

glm::mat4& Camera::get_translate(){
    translate_matrix = glm::translate(glm::mat4(1.0f), pos);
    return translate_matrix;
}

glm::mat4& Camera::get_view_matrix(){
    glm::vec3 yvec(0, 1.0f, 0);
    glm::vec3 xvec(1.0f, 0, 0);
    glm::quat vertical_quat = glm::angleAxis(glm::radians(static_cast<float>(delta_pos_y)), xvec);
    glm::quat horizontal_quat = glm::angleAxis(glm::radians(static_cast<float>(delta_pos_x)), yvec);

    look_vector = horizontal_quat * look_vector;
    look_vector = vertical_quat * look_vector;

    //Why do you need to add the position? because it is not thinking as a basis for some reason.
    view_matrix = glm::lookAt(pos, pos+look_vector , yvec);

    return view_matrix;
}