#version 330 core 

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 vertColor;
out vec2 vertUV;
out vec2 vertPos;

uniform mat4 P;

void main() {
    gl_Position.xy = (P*vec4(vertexPosition, 0.0, 1.0)).xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    vertColor = vertexColor;
    vertUV = vertexUV;
    vertPos = vertexPosition;
}
