#ifndef SHADERS_H
#define SHADERS_H

#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

typedef struct {
  unsigned int vao;
  unsigned int vbo;
} buff_obj;

void shaders(const char *v_shader, const char *f_shader,
             unsigned int &shader_program);
void setup_vbo(buff_obj &obj, float *vertices, size_t size);

#endif
