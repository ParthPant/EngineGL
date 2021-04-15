#version 330 core 

out vec4 color;

in vec4 vertColor;
in vec2 vertUV;
in vec2 vertPos;

uniform sampler2D sampler;

void main() {
    vec4 textureColor = texture(sampler, vertUV);

    if (textureColor == vec4(0.0f, 0.0f, 0.0f, 0.0f))
    {
        color = vertColor;
    }
    else
    {
        color = vertColor * textureColor;
    }
}
