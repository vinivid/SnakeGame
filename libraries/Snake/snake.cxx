#include "snake.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include "control.hpp"
#include "glm/fwd.hpp"
#include <shaders.hpp>
#include "fruit.hpp"

Snake::Snake(){
    v[0].x = 0.05f;
    v[0].y = 0.05f;
    v[0].dir = right;
}

/*The way the movement is organized by the distance of one of the vertices to the center
will be the normalized distance to travel a single square
EG: the snake starts at 0.05 and to travel one block it moves 0.05
*/

void Snake::move(){
    float c_time = static_cast<float>(glfwGetTime());
    delta_time = c_time - previous_time;
    previous_time = c_time;

     std::cout << "delta time "<< delta_time << "\n";

    for(auto i = 0; i < v.size(); i++){
        std::cout << "X pos: "<< v[i].x << " Y pos: " << v[i].y << "\n";

        if(v[i].x <= 1 && v[i].x >= -1 && v[i].y <= 1 && v[i].y >= -1){
            switch(v[i].dir){
                case up:
                    v[i].y += 0.5f * delta_time;
                    break;
                case down:
                    v[i].y -= 0.5f * delta_time;
                    break;
                case left:
                    v[i].x += 0.5f * delta_time;
                    break;
                case right:
                    v[i].x -= 0.5f * delta_time;
                    break;
                case stop:
                    v[i].x = 0.2f;
                    v[i].y = 0.2f;
                    break;
                default:
                    v[i].x += 0.05f;
                    break;
            }
        }else{
            v[i].x = 0.05f;
            v[i].y = 0.05f;
        }    
    }
}

void Snake::key_press(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        v[0].dir = up;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        v[0].dir = left;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        v[0].dir = down;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        v[0].dir = right;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        v[0].dir = stop;
    }
}

void Snake::draw_snake(Control &ctrl, Shader &shd){
    glUseProgram(shd.ID);
    glm::vec3 zaxis(0,0,1);

    for(auto i:v){
        ctrl.add_translate(i.x, i.y, 2);
        ctrl.add_rotate(static_cast<float>(i.dir), zaxis);
        ctrl.make_comb_mat();

        shd.set_uniform_mat4f("translate", ctrl.comb_mat_pointer());

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(6*sizeof(float)));
    }

}