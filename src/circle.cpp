#include "../include/headers/circle.h"


void generate_circle_vertices(buff_obj &obj, float radius, int segments) {
    int num_vertices = segments + 2;
    float *vertices = new float[num_vertices * 3];
    

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    
    for(int i=0; i<=segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        vertices[(i+1)*3 + 0] = radius * cos(angle);
        vertices[(i+1)*3 + 1] = radius * sin(angle);
        vertices[(i+1)*3 + 2] = 0.0f;
    }
    
    setup_vbo(obj, vertices, num_vertices * 3 * sizeof(float));

    delete[] vertices;
}
