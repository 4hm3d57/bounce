#include "../include/headers/shaders.h"


void shaders(const char* v_shader, const char* f_shader, unsigned int& shader_program){
        // vertex shader
    std::ifstream vert_file(v_shader);
    if(!vert_file.is_open()){
        std::cerr << "[LOG]: FAILED TO OPEN VERTEX SHADER FILE" << std::endl;
        return;
    }

    std::stringstream vert_stream;
    vert_stream << vert_file.rdbuf();
    std::string vert_string = vert_stream.str();
    const char* vertex_code = vert_string.c_str();
    vert_file.close();
    
    // fragment shader
    std::ifstream frag_file(f_shader);
    if(!frag_file.is_open()){
        std::cerr << "[LOG]: FAILED TO OPEN FRAGMENT SHADER FILE" << std::endl;
        return;
    }

    std::stringstream frag_stream;
    frag_stream << frag_file.rdbuf();
    std::string frag_string = frag_stream.str();
    const char* frag_code = frag_string.c_str();
    frag_file.close();

    // compile both shaders
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_code, NULL);
    glCompileShader(vertex_shader);

    int success;
    char infolog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, infolog);
        std::cerr << "Vertex shader compilation failed: " << infolog << std::endl;
        return;
    }

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &frag_code, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, infolog);
        std::cerr << "fragment shader compilation failed: " << infolog << std::endl;
        return;
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shader_program, 512, nullptr, infolog);
        std::cerr << "Shader program linking failed: " << infolog << std::endl;
        return;
    }

    // cleanup
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}



void setup_vbo(buff_obj& obj, float *vertices, size_t size) {
    glGenVertexArrays(1, &obj.vao);
    glBindVertexArray(obj.vao);

    glGenBuffers(1, &obj.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
