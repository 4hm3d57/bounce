#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/headers/shaders.h"

#define WIDTH 800
#define HEIGHT 600


void exit_key(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        std::cout << "Exitting..." << std::endl;
        glfwSetWindowShouldClose(window, true);
    }
}


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bounce", NULL, NULL);
    if(!window){
        std::cout << "Failed to load window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "glad failed!" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    
    unsigned int shader_program;
    buff_obj obj;

    float vertices[] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    
    shaders("shaders/shader.vert", "shaders/shader.frag", shader_program);
    setup_vbo(obj, vertices, sizeof(vertices));

    
    while(!glfwWindowShouldClose(window)){
        exit_key(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(obj.vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    return 0;
}

