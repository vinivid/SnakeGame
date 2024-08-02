/* Made by ViniVid
   https://github.com/vinivid/SnakeGame
   Contact: frato.vini@gmail.com
*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "control.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"

void Control::add_rotate(float angle, glm::vec3 &v){
    is_comb_mat_calc = false;
    rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), v);
}

void Control::add_translate(float x, float y, float z){
    is_comb_mat_calc = false;
    translate = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));
}

void Control::add_scale(float x, float y, float z){
    is_comb_mat_calc = false;
    scale = glm::scale(glm::mat4(1.0f), glm::vec3(x,y,z));
}

void Control::add_perspective_frustum(float fov, float width, float height, float near, float far){
    is_comb_mat_calc = false;
    perspective_frustum = glm::perspective(glm::radians(fov), static_cast<float>(width/height), near, far);
}

void Control::set_view_mat(glm::mat4& mat){
    is_comb_mat_calc = false;
    view_matrix = mat;
}

void Control::make_comb_mat(){
    if(is_comb_mat_calc){
        return;
    }else{
        comb_mat = perspective_frustum * view_matrix* translate  * scale * rotate;
    }
}

[[nodiscard]] float* Control::rotate_pointer(){
    return glm::value_ptr(rotate);
}

[[nodiscard]] float* Control::translate_pointer(){
    return glm::value_ptr(translate);
}

[[nodiscard]] float* Control::scale_pointer(){
    return glm::value_ptr(scale);
}

[[nodiscard]] float* Control::persepective_poiter(){
    return glm::value_ptr(perspective_frustum);
}

[[nodiscard]] float* Control::comb_mat_pointer(){
    return  glm::value_ptr(comb_mat);
}