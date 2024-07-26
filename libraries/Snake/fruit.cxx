#include <glad/glad.h>
#include "fruit.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <iterator>
#include <set>
#include "shaders.hpp"
#include "control.hpp"

fruit::fruit(){
    pos_x = -0.50f;
    pos_y = 0.05f;
}

void fruit::gen_new_fruit(const std::set<unsigned> &occupied){
    //Gets a random value in the set of available positions
    unsigned elemet_acces = std::rand() % occupied.size();
    auto it = occupied.begin();
    std::advance(it, elemet_acces);
    unsigned pos = *it;

    unsigned row = pos/20;
    unsigned colum = pos%20;
    
    //This is a simple condition so the colums and rows can be transformed to coordinates
    //to render
    //the casting is necessary because the position is float and 10 - coordinate should give 
    //negative numbers
    pos_y =  ((10 - static_cast<float>(row)) - 0.5f)/10;
    pos_x = ((10 - static_cast<float>(colum)) - 0.5f)/10;
}


//Draws the fruit with a little rotation
void fruit::draw_fruit(Control& ctrl, Shader &shd){
    glUseProgram(shd.ID);
    glm::vec3 zaxis(0,0,1);

    ctrl.add_translate(pos_x, pos_y, 2);
    ctrl.add_rotate(static_cast<float>(6*glfwGetTime()), zaxis);
    ctrl.make_comb_mat();

    shd.set_uniform_mat4f("translate", ctrl.comb_mat_pointer());

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(6*sizeof(float)));
}