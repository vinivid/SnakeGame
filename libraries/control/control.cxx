#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "control.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"

Control::Control(){
    rotate = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    perspective_frustum = glm::mat4(1.0f);
    comb_mat = glm::mat4(1.0f);
    view_matrix = glm::mat4(1.0f);
}

void Control::add_rotate(float angle, glm::vec3 &v){
    rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), v);
}

void Control::add_translate(float x, float y, float z){
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));
}

void Control::add_scale(float x, float y, float z){
    scale = glm::scale(glm::mat4(1.0f), glm::vec3(x,y,z));
}

void Control::add_perspective_frustum(float fov, float width, float height, float near, float far){
    perspective_frustum = glm::perspective(glm::radians(fov), static_cast<float>(width/height), near, far);
}

void Control::set_view_mat(glm::mat4& mat){
    view_matrix = mat;
}

void Control::make_comb_mat(){
    comb_mat = perspective_frustum * view_matrix* translate  * scale * rotate;
}

float* Control::rotate_pointer(){
    return glm::value_ptr(rotate);
}

float* Control::translate_pointer(){
    return glm::value_ptr(translate);
}

float* Control::scale_pointer(){
    return glm::value_ptr(scale);
}

float* Control::persepective_poiter(){
    return glm::value_ptr(perspective_frustum);
}

float* Control::comb_mat_pointer(){
    return  glm::value_ptr(comb_mat);
}