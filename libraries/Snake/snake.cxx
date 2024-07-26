#include "snake.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <utility>
#include <set>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include "control.hpp"
#include "glm/fwd.hpp"
#include <shaders.hpp>
#include "fruit.hpp"

Snake::Snake(){
    //initializes all posible position for the fruit
    for(int i = 0; i < 400; i++) positions.insert(i);
    positions.erase(185);
    positions.erase(184);
    positions.erase(183);

    //sets the heaad of the snake
    v[0].x = 0.05f;
    v[0].y = 0.05f;
    v[0].scale = 1;
    v[0].dir = right;

    //initializes the other three body parts
    for(int i = 1; i < v.size(); i++){
        switch(v[i-1].dir){
                case up:
                    v[i].x = v[i-1].x;
                    v[i].y -= v[i-1].y + 0.1f;
                    break;
                case down:
                    v[i].x = v[i-1].x;
                    v[i].y += v[i-1].y + 0.1f;
                    break;
                case left:
                    v[i].y = v[i-1].y;
                    v[i].x -= v[i-1].x +0.1f;
                    break;
                case right:
                    v[i].y = v[i-1].y;
                    v[i].x += v[i-1].x + 0.1f;
                    break;
                default:
                    std::cout << "Body part " << i-1 << "has no valid direction\n";
                    break;
        }

        v[i].dir = v[i-1].dir;
        v[i].scale = v[i-1].scale - 0.025f;
    }
}

/*The snake moves 0.1f to the direction of its head every routine, wich should be
about 0.1s. It is necessary to make it so the snake walks in such way so every
change will be delimited to the coordinate system.
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
                default:
                    std::cout << "Body part " << i << "has no valid direction\n";
                    break;
            }
        }else{
            v[i].x = 0.05f;
            v[i].y = 0.05f;
        }    
    }

    if(!(count_cicle)){
        if(!index_turn.empty()){
            if(index_turn.back().first >= v.size()){
                index_turn.pop_back();
            }

            for(auto& it:index_turn){
                v[it.first].dir = it.second;
                it.first += 1;
            }
        }
        used_queue = false;
        count_cicle = routine_time;
    }
}

void Snake::key_press(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        if(!used_queue){
            index_turn.push_front(std::pair<int, direction>(0, up));
            used_queue = true;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        if(!used_queue){
            index_turn.push_front(std::pair<int, direction>(0, left));
            used_queue = true;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        if(!used_queue){
             index_turn.push_front(std::pair<int, direction>(0, down));
             used_queue = true;
        }
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        if(!used_queue){
             index_turn.push_front(std::pair<int, direction>(0, right));
             used_queue = true;
        }
    }
}

void Snake::draw_snake(Control &ctrl, Shader &shd){
    glUseProgram(shd.ID);
    glm::vec3 zaxis(0,0,1);

    for(auto i:v){
        ctrl.add_translate(i.x, i.y, 2);
        ctrl.add_rotate(static_cast<float>(i.dir), zaxis);
        ctrl.add_scale(1.0f, i.scale, 1.0f);
        ctrl.make_comb_mat();

        shd.set_uniform_mat4f("translate", ctrl.comb_mat_pointer());

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(6*sizeof(float)));
    }

}