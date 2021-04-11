#version 330 core 

in vec2 vertexPosition;
out vec2 position;

void main() {
    gl_Position.xy = vertexPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    position = vertexPosition;
}
