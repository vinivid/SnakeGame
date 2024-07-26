#pragma once

#include <glad/glad.h>
#include "shaders.hpp"
#include "control.hpp"
#include <set>

struct fruit{
    float pos_x;
    float pos_y;
    int pos_coord;

    fruit();

    void gen_new_fruit(const std::set<int> &occupied);
    void draw_fruit(Control& ctrl, Shader &shd);
};