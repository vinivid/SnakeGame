#include "snake.hpp"

#include <glad/glad.h>
#include <stack>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include "control.hpp"
#include "glm/fwd.hpp"
#include <shaders.hpp>
#include "fruit.hpp"

Snake::Snake(){
    v[0].x = 0;
    v[0].y = 0;
    v[0].dir = right;
}

void Snake::move(){
    for(auto i = 0; i < v.size(); i++){
        switch(v[i].dir){
            case up:
                v[i].y += 0.01f;
                break;
            case down:
                v[i].y -= 0.01f;
                break;
            case left:
                v[i].x -= 0.01f;
                break;
            case right:
                v[i].x += 0.01f;
                break;
            default:
                v[i].x += 0.01f;
                break;
        }
    }
}

void Snake::draw_snake(Control &ctrl, Shader &shd){
    glUseProgram(shd.ID);
    glm::vec3 zaxis(0,0,1);

    for(auto i:v){
        ctrl.add_translate(i.x, i.y, 1);
        ctrl.add_rotate(static_cast<float>(i.dir), zaxis);
        ctrl.make_comb_mat();

        shd.set_uniform_mat4f("translate", ctrl.comb_mat_pointer());

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(6*sizeof(float)));
    }

}