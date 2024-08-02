#pragma once

#include <glad/glad.h>
#include <list>
#include <utility>
#include <vector>
#include <GLFW/glfw3.h>
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
    float scale;
    direction dir;
};

class Snake{
    private:
        std::set<int> positions;
        std::list<std::pair<int, direction>> index_turn;
        std::vector<body_part> v{3};
        //Todo change variable names to be more apropiate
        //Todo make it so the movement of the snake is not dependent on framerate
        int routine_time = 6;
        int count_cicle = 6;
        bool used_queue = false;
        float routine_change = 0.017f;
        int prev_removed = 185;
        int prev_added = 183;

        void add_part();
        [[nodiscard]] auto check_next_pos(int row_next, int colum_next, fruit& frt) noexcept->int;
        void init_snake();
        void manage_prev_added();
    public:
        Snake();

        [[nodiscard]] auto move(fruit& frt) noexcept ->int;
        void key_press(GLFWwindow *window);
        void draw_snake(Control &ctrl, Shader &shd);
        void new_snake();
};