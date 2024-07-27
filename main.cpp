/* Made by ViniVid
   https://github.com/vinivid/SnakeGame
   Contact: frato.vini@gmail.com
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/fwd.hpp"
#include "headers/snake.hpp"
#include "shaders.hpp"
#include "control.hpp"
#include "camera.hpp"
#include "snake.hpp"
#include "fruit.hpp"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    Shader test_shader("vertex.glsl", "fragment.glsl");

    test_shader.use();

    float vertices[] = {
        //Square
        -1.15f, -1.0f, 2.01f,  0.211f, 0.211f, 0.211f,
        -1.15f,  1.0f, 2.01f,  0.211f, 0.211f, 0.211f,
         0.9f, -1.0, 2.01f,  0.211f, 0.211f, 0.211f,
         0.9f,  1.0f, 2.01f,  0.211f, 0.211f, 0.211f,

        //Parallelepiped
        -0.05f, -0.05f,  -0.05f, 0.5f, 0.5f, 0.5f,
         0.05f, -0.05f,  -0.05f, 0.1f, 0.1f, 0.1f,
         0.05f, -0.05f,  0.05f, 0.3f, 0.3f, 0.3f,
         -0.05f, -0.05f, 0.05f, 0.0f, 1.0f, 0.0f,
         -0.05f,  0.05f, 0.05f, 0.0f, 0.0f, 1.0f,
         -0.05f, 0.05f,  -0.05f, 1.0f, 0.0f, 0.0f, 
         0.05f,  0.05f,  -0.05f, 0.0f, 0.25f, 0.5f, 
         0.05f, 0.05f,  0.05f, 0.75f, 0.10f, 0.0f,
    };

    unsigned int indexes[] = {
        //rectangle
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

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

    Control ctt;
    Camera sts;
    Snake snk;
    fruit frt;

    glfwSetCursorPos(window, 0, 0);
    ctt.add_perspective_frustum(60.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);

    glm::vec3 v(0,0,1);

    while(!glfwWindowShouldClose(window))
    {   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        test_shader.use();

        ctt.add_translate(0, 0, 0);
        ctt.add_rotate(0, v);
        ctt.add_scale(1, 1,1);
        ctt.make_comb_mat();

        test_shader.set_uniform_mat4f("translate", ctt.comb_mat_pointer());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSetCursorPos(window, 0, 0);
        sts.read_keyboard(window);
        sts.read_mouse(window);
        ctt.set_view_mat(sts.get_view_matrix());

        snk.key_press(window);
        if(snk.move(frt))
            if(!handle_end(snk))
                return 0;
            
        snk.draw_snake(ctt, test_shader);
        frt.draw_fruit(ctt, test_shader);

        glfwSwapBuffers(window);
        process_input(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}