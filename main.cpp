#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders.hpp"
#include "control.hpp"
#include "camera.hpp"
#include "snake.hpp"

void process_input(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    unsigned int texture1;
    glGenTextures(1, &texture1);

    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float vertices[] = {
        //Square
        -0.5f, -0.5f, 0.0f,  0.211f, 0.211f, 0.211f,
        -0.5f,  0.5f, 0.0f,  0.211f, 0.211f, 0.211f,
         0.5f, -0.5f, 0.0f,  0.211f, 0.211f, 0.211f,
         0.5f,  0.5f, 0.0f,  0.211f, 0.211f, 0.211f,

        //Paralelepied
        -0.05f, -0.1f,  -0.05f, 0.5f, 0.5f, 0.5f,// 0 4
         0.05f, -0.1f,  -0.05f, 0.1f, 0.1f, 0.1f,// 1 5
         0.05f, -0.1f,  0.05f, 0.3f, 0.3f, 0.3f,// 2 6
         -0.05f, -0.1f, 0.05f, 0.0f, 1.0f, 0.0f,// 3 7
         -0.05f,  0.1f, 0.05f, 0.0f, 0.0f, 1.0f,//4 8
         -0.05f, 0.1f,  -0.05f, 1.0f, 0.0f, 0.0f, // 5 9
         0.05f,  0.1f,  -0.05f, 0.0f, 0.25f, 0.5f, // 6 10
         0.05f, 0.1f,  0.05f, 0.75f, 0.10f, 0.0f, // 7 11

    };

    unsigned int indexes[] = {
        //rectangle
        0,1,2,
        3,1,2,

        //Paralele
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

    glfwSetCursorPos(window, 0, 0);
    ctt.add_perspective_frustum(90.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(VAO);

    while(!glfwWindowShouldClose(window))
    {   
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        test_shader.use();

        sts.read_keyboard(window);
        sts.read_mouse(window);
        ctt.set_view_mat(sts.get_view_matrix());

        snk.move();
        snk.draw_snake(ctt, test_shader);

        glfwSwapBuffers(window);
        process_input(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}