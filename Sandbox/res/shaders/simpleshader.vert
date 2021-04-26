#version 330 core 

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;

out vec4 vertColor;

uniform mat4 ViewProjection;

void main() {
    gl_Position = ViewProjection * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
    vertColor = vertexColor;
}
