#version 330 core 

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 vertColor;
out vec2 vertUV;

void main() {
    gl_Position.xy = vertexPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    vertColor = vertexColor;
    vertUV = vertexUV;
}
