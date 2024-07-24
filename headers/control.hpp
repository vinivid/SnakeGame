#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
    
class Control{
    private:
        glm::mat4 rotate;
        glm::mat4 translate;
        glm::mat4 scale;
        glm::mat4 view_matrix;
        glm::mat4 perspective_frustum;
        glm::mat4 comb_mat;        
    public:
        Control();

        void add_rotate(float angle, glm::vec3 &v);
        void add_translate(float x, float y, float z);
        void add_scale(glm::vec3 &v);
        void add_perspective_frustum(float fov, float width, float height, float near, float far);

        void set_view_mat(glm::mat4& mat);

        void make_comb_mat(); 

        float* rotate_pointer();
        float* translate_pointer();
        float* scale_pointer();
        float* persepective_poiter();
        float* comb_mat_pointer();
};

