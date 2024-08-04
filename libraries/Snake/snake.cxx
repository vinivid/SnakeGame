/* Made by ViniVid
   https://github.com/vinivid/SnakeGame
   Contact: frato.vini@gmail.com
*/

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
#include <chrono>
#include <thread>

Snake::Snake(){
    init_snake();
}

[[nodiscard]] auto Snake::move(fruit& frt) noexcept->int{
    count_cicle -= 1;

    for(auto i = 0; i < v.size(); i++){
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
        
        int row_prev = prev_removed/20;
        int colum_prev = prev_removed%20;
        int res = 0;

        switch(v[0].dir){
            case up:
                row_prev -= 1;
                prev_removed -= 20;
                res = check_next_pos(row_prev, colum_prev,frt);
                if(res == 0){
                    manage_prev_added();
                }else if(res == 1){
                    return 1;
                }

                positions.erase(prev_removed);
                break;
            case down:
                row_prev += 1;
                prev_removed += 20;
                res = check_next_pos( row_prev,colum_prev,frt);
                if(res == 0){
                    manage_prev_added();
                }else if(res == 1){
                    return 1;
                }

                positions.erase(prev_removed);
                break;
            case left:
                colum_prev -= 1;
                prev_removed -= 1;
                res = check_next_pos(row_prev, colum_prev,frt);
                if(res == 0){
                    manage_prev_added();
                }else if(res == 1){
                    return 1;
                }

                positions.erase(prev_removed);
                break;
            case right:
                colum_prev += 1;
                prev_removed += 1;
                res = check_next_pos(row_prev, colum_prev, frt);
                if(res == 0){
                    manage_prev_added();
                }else if(res == 1){
                    return 1;
                }

                positions.erase(prev_removed);
                break;
            default:
                break;
        }

        used_queue = false;
        count_cicle = routine_time;
    }

    return 0;
}

void Snake::key_press(GLFWwindow *window){
    if(v[0].dir != down && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        if(!used_queue){
            index_turn.push_front(std::pair<int, direction>(0, up));
            used_queue = true;
        }
    }
    if(v[0].dir != right && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        if(!used_queue){
            index_turn.push_front(std::pair<int, direction>(0, left));
            used_queue = true;
        }
    }
    if(v[0].dir != up && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        if(!used_queue){
             index_turn.push_front(std::pair<int, direction>(0, down));
             used_queue = true;
        }
    }
    if(v[0].dir != left && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
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
        if(i.dir == left || i.dir == right){
            ctrl.add_scale(1.0f, i.scale, 1.0f);
        }else{
            ctrl.add_scale(i.scale, 1.0f, 1.0f);
        }
        ctrl.make_comb_mat();

        shd.update_shader("translate", ctrl.comb_mat_pointer());

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(6*sizeof(float)));
    }
}

void Snake::new_snake(){
    v.resize(3);
    init_snake();
    index_turn.resize(0);
    prev_removed = 183;
    prev_removed = 185;
    used_queue = false;
    count_cicle = 6;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
}

void Snake::add_part(){
    body_part to_add;
    to_add.x = 0; to_add.y = 0; to_add.scale = 1; to_add.dir = right;

    positions.erase(prev_added);
    switch(v[v.size() - 1].dir){
        case up:
            to_add.x = v[v.size() - 1].x;
            to_add.y = v[v.size() - 1].y;
            to_add.y -= 0.1f;
            break;
        case down:
            to_add.x = v[v.size() - 1].x;
            to_add.y = v[v.size() - 1].y;
            to_add.y += 0.1f;
            break;
        case left:
            to_add.y = v[v.size() - 1].y;
            to_add.x = v[v.size() - 1].x;
            to_add.x -= 0.1f;
            break;
        case right:
            to_add.y = v[v.size() - 1].y;
            to_add.x = v[v.size() - 1].x;
            to_add.x += 0.1f;
            break;
        default:
            std::cout << "Body part " << v.size() - 1 << "has no valid direction\n";
            break;
    }

    to_add.dir = v[v.size() - 1].dir;
    to_add.scale = v[v.size() - 1].scale - 0.0024f;

    v.push_back(to_add);
}

[[nodiscard]] auto Snake::check_next_pos(int row_next, int colum_next, fruit& frt) noexcept -> int{
    if(prev_removed == frt.pos_coord){
        add_part();
        frt.gen_new_fruit(positions);
        return 2;
    }
    
    if(row_next <= -1 || row_next >= 20 || colum_next >= 20 || colum_next <= -1 || positions.find(prev_removed) == positions.end()){
        return 1;
    }
    return 0;
}

void Snake::init_snake(){
    for(int i = 0; i < 400; i++) positions.insert(i);
    positions.erase(185);
    positions.erase(184);
    positions.erase(183);

    v[0].x = 0.45f;
    v[0].y = 0.05f;
    v[0].scale = 1;
    v[0].dir = right;

    for(int i = 1; i < v.size(); i++){
        switch(v[i-1].dir){
                case up:
                    v[i].x = v[i-1].x;
                    v[i].y = v[i-1].y;
                    v[i].y -= 0.1f;
                    break;
                case down:
                    v[i].x = v[i-1].x;
                    v[i].y = v[i-1].y;
                    v[i].y += 0.1f;
                    break;
                case left:
                    v[i].y = v[i-1].y;
                    v[i].x = v[i-1].x;
                    v[i].x -= 0.1f;
                    break;
                case right:
                    v[i].y = v[i-1].y;
                    v[i].x = v[i-1].x;
                    v[i].x += 0.1f;
                    break;
                default:
                    std::cout << "Body part " << i-1 << "has no valid direction\n";
                    break;
        }

        v[i].dir = v[i-1].dir;
        v[i].scale = v[i-1].scale - 0.0024f;
    }
}

void Snake::manage_prev_added(){
    positions.insert(prev_added);
    switch(v[v.size()-1].dir){
            case up:
                prev_added -= 20;
                break;
            case down:
                prev_added += 20;
                break;
            case left:
                prev_added -= 1;
                break;
            case right:
                prev_added += 1;
                break;
            default:
                break;
        }
}