#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/headers/shaders.h"
#include "../include/headers/circle.h"

#define WIDTH 800
#define HEIGHT 600
#define rad 0.5f


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
    buff_obj circle;

    float vertices[] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    float x = 0.0f, y = 0.0f;
    float vx = 0.01f, vy = 0.01f;
    
    shaders("shaders/shader.vert", "shaders/shader.frag", shader_program);
    setup_vbo(obj, vertices, sizeof(vertices));
    
    generate_circle_vertices(circle, rad, 80);
    
    while(!glfwWindowShouldClose(window)){
        exit_key(window);

        // update position
        x += vx;
        y += vy;

        // bounce logic
        if(x + rad > 1.0f || x - rad < -1.0f) vx = -vx;
        if(y + rad > 1.0f || y - rad < -1.0f) vy = -vy;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(circle.vao);
        int posloc = glGetUniformLocation(shader_program, "uPos");
        glUniform2f(posloc, x, y);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 92);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glfwTerminate();
    return 0;
}

