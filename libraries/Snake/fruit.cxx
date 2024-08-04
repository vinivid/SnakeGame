/* Made by ViniVid
   https://github.com/vinivid/SnakeGame
   Contact: frato.vini@gmail.com
*/

#include <glad/glad.h>
#include "fruit.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <iterator>
#include <set>
#include "shaders.hpp"
#include "control.hpp"

fruit::fruit(){
    pos_x = -0.70f;
    pos_y = 0.05f;
    pos_coord = 195;
}

void fruit::gen_new_fruit(const std::set<int> &occupied){
    if(occupied.size() <= 0){
        std::cout << "no spaces left to generate new fruit\n";
        return;
    }

    int elemet_acces = std::rand() % occupied.size();
    auto it = occupied.begin();
    std::advance(it, elemet_acces);
    pos_coord = *it;

    int row = pos_coord/20;
    int colum = pos_coord%20;
    
    pos_y =  ((10 - static_cast<float>(row)) - 0.5f)/10;
    pos_x = ((10 - static_cast<float>(colum)) - 1.5f)/10;
}


//Draws the fruit with a little rotation
void fruit::draw_fruit(Control& ctrl, Shader &shd){
    glUseProgram(shd.ID);
    glm::vec3 zaxis(0,0,1);

    ctrl.add_translate(pos_x, pos_y, 2);
    ctrl.add_rotate(static_cast<float>(6*glfwGetTime()), zaxis);
    ctrl.add_scale(0.5, 0.5, 1);
    ctrl.make_comb_mat();

    shd.update_shader("translate", ctrl.comb_mat_pointer());

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(12*sizeof(float)));
}