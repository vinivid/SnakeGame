#include "snake.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stack>
#include <set>
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
    previous_time = static_cast<float>(glfwGetTime());
}

/*The way the movement is organized by the distance of one of the vertices to the center
will be the normalized distance to travel a single square
EG: the snake starts at 0.05 and to travel one block it moves 0.05
*/

void Snake::move(){
    count_cicle -= 1;

    //std::cout << "pos x: " << v[0].x << " pos y: " << v[0].y << "\n"; 

    for(auto i = 0; i < v.size(); i++){
        if(v[i].x <= 1 && v[i].x >= -1 && v[i].y <= 1 && v[i].y >= -1){
            switch(v[i].dir){
                case up:
                    v[i].y += routine_change;
                    break;
                case down:
                    v[i].y -= routine_change;
                    break;
                case left:
                    v[i].x += routine_change;
                    break;
                case right:
                    v[i].x -= routine_change;
                    break;
                case stop:
                    v[i].x = 0.05f;
                    v[i].y = 0.05f;
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

    if(!(count_cicle)){
        if(dir_change.first){
            v[0].dir = dir_change.second;
            dir_change.first = 0;
        }
        count_cicle = routine_time;
    }
}

void Snake::key_press(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        dir_change.first = 1;
        dir_change.second = up;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        dir_change.first = 1;
        dir_change.second = left;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        dir_change.first = 1;
        dir_change.second = down;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        dir_change.first = 1;
        dir_change.second = right;
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