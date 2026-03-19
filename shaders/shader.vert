#version 330 core
layout (location=0) in vec3 aPos;
uniform vec2 uPos;
uniform float aspect;

void main() {
    float correctedX = (aPos.x + uPos.x) / aspect;

    float correctedY = aPos.y + uPos.y;
    gl_Position = vec4(correctedX, correctedY, aPos.z, 1.0);
}
