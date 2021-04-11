#version 330 core 

out vec4 color;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D sampler;
uniform sampler2D sampler2;

void main() {
    vec4 textureColor = mix(texture(sampler, vertUV), texture(sampler2, vertUV), 0.5);
    color = textureColor;
}
