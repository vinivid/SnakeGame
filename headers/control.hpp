#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
    
class Control{
    private:
        glm::mat4 rotate{1.0f};
        glm::mat4 translate{1.0f};
        glm::mat4 scale{1.0f};
        glm::mat4 view_matrix{1.0f};
        glm::mat4 perspective_frustum{1.0f};
        glm::mat4 comb_mat{1.0f};

        bool is_comb_mat_calc = false;        
    public:
        Control() {};

        void add_rotate(float angle, glm::vec3 &v);
        void add_translate(float x, float y, float z);
        void add_scale(float x, float y, float z);
        void add_perspective_frustum(float fov, float width, float height, float near, float far);

        void set_view_mat(glm::mat4& mat);

        void make_comb_mat(); 

        [[nodiscard]] float* rotate_pointer();
        [[nodiscard]] float* translate_pointer();
        [[nodiscard]] float* scale_pointer();
        [[nodiscard]] float* persepective_poiter();
        [[nodiscard]] float* comb_mat_pointer();
};

