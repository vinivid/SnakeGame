/* Made by ViniVid
   https://github.com/vinivid/SnakeGame
   Contact: frato.vini@gmail.com
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "glm/fwd.hpp"
#include "headers/snake.hpp"
#include "shaders.hpp"
#include "control.hpp"
#include "camera.hpp"
#include "snake.hpp"
#include "fruit.hpp"
#include "gl_objects.hpp"

void process_input(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int handle_end(Snake &snk){
    std::cout << "Game over!\nDo you wish to continue? [y/n]\n";
    std::string answer = "a";

    while(answer != "y" && answer != "n"){
        std::cin >> answer;
    }

    if(answer == "y"){
        snk.new_snake();
        return 1;
    }else{
        std::cout << "Bye!\n";
        return 0;
    }
    return 1;
}

int main(void){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_POSITION_X, 500);
    glfwWindowHint(GLFW_POSITION_Y, 250);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Camera", NULL, NULL);

    if(window == NULL){
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))){
        std::cout << "Failed to initialize glad\n";
        return -1;
    }

    Shader main_shader("vertex.glsl", "fragment.glsl");

    main_shader.use();

    std::vector<float> posv = {
        //Square
        -1.15f, -1.0f, 2.01f,
        -1.15f,  1.0f, 2.01f,
        0.9f, -1.0, 2.01f,
        0.9f,  1.0f, 2.01f,

        //Parallelepiped
        -0.05f, -0.05f,  -0.05f,
        0.05f, -0.05f,  -0.05f,
        0.05f, -0.05f,  0.05f,
        -0.05f, -0.05f, 0.05f,
        -0.05f,  0.05f, 0.05f,
        -0.05f, 0.05f,  -0.05f,
        0.05f,  0.05f,  -0.05f,
        0.05f, 0.05f,  0.05f,
    };

    std::vector<float> normals = {
        //square
        0.211f, 0.211f, 0.211f,
        0.211f, 0.211f, 0.211f,
        0.211f, 0.211f, 0.211f,
        0.211f, 0.211f, 0.211f,

        //Parallelepiped
        0.5f, 0.5f, 0.5f,
        0.1f, 0.1f, 0.1f,
        0.3f, 0.3f, 0.3f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.25f, 0.5f,
        0.75f, 0.10f, 0.0f
    };

    std::vector<float> tx = {
        0, 0,
        0, 0,
        0, 0,
        0, 0,

        0,0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0
    };

    std::vector<unsigned> indexes= {
        //square
        0,1,2,
        3,1,2,
        //Parallelepiped
        4,5,6,
        7,4,6,
        4,5,10,
        9,4,10,
        5,6,10,
        10,11,6,
        6,11,7,
        8,11,7,
        8,7,9,
        9,4,7,
        8,11,9,
        9,10,11
    };

    vertex idk;
    idk.pos = posv;
    idk.normal = normals;
    idk.texture = tx;

    indexes_obj idc = indexes;

    gl_objects objj(1);
    objj.config_vbo(0, idk);
    objj.config_ibo(0, idc);
    objj.config_vao(0);

    Control ctt;
    Camera sts;
    Snake snk;
    fruit frt;

    glfwSetCursorPos(window, 0, 0);
    ctt.add_perspective_frustum(60.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    objj.bind_vao(0);

    glm::vec3 v(0,0,1);

    while(!glfwWindowShouldClose(window))
    {   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        main_shader.use();

        ctt.add_translate(0, 0, 0);
        ctt.add_rotate(0, v);
        ctt.add_scale(1, 1,1);
        ctt.make_comb_mat();

        main_shader.update_shader("translate", ctt.comb_mat_pointer());

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glfwSetCursorPos(window, 0, 0);
        sts.read_keyboard(window);
        sts.read_mouse(window);
        ctt.set_view_mat(sts.get_view_matrix());

        snk.key_press(window);
        if(snk.move(frt))
            if(!handle_end(snk))
                return 0;
            
        snk.draw_snake(ctt, main_shader);
        frt.draw_fruit(ctt, main_shader);

        glfwSwapBuffers(window);
        process_input(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}