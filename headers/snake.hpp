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
        int routine_time = 6;
        int count_cicle = 6;
        bool used_queue = false;
        float routine_change = 0.017f;
        int prev_removed = 183;
        int prev_added = 185;

        void add_part();
        int check_next_pos(int p_added, int row_next, int colum_next, fruit& frt);
        void init_trhee();
    public:
        Snake();

        int move(fruit& frt);
        void key_press(GLFWwindow *window);
        void draw_snake(Control &ctrl, Shader &shd);
        void new_snake();
};