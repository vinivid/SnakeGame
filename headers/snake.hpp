#pragma once

#include <stack>
#include <utility>
#include <vector>
#include <glm/glm.hpp>
#include "control.hpp"
#include "shaders.hpp"
#include "fruit.hpp"

enum direction{
    up = 0,
    left = 90,
    right = -90,
    down = 180
};

struct body_part{
    float x;
    float y;
    direction dir;
};

//The snake doesn't depend on the fruit but the fruit depens on the snake
class Snake{
    private:   
        std::stack<std::pair<int, direction>> index_turn;
        std::vector<body_part> v{1};
    public:
        Snake();

        void move();
        void draw_snake(Control &ctrl, Shader &shd);
        void check_fruit(fruit& fruit);
};