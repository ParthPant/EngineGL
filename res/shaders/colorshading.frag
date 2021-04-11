#version 330 core 

out vec3 color;
in vec2 position;

void main() {
    color = vec3(1.0, 1.0, 0.0) + vec3(position, 0.0);
}
