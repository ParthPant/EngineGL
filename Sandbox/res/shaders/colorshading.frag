#version 330 core 

out vec4 color;

in vec4 vertColor;
in vec2 vertUV;

uniform sampler2D sampler;
uniform float time;

void main() {
    vec4 textureColor = texture(sampler, vertUV);
    color = textureColor * vertColor * vec4(0.5*(sin(5*time+0.0)+1.0),
                                            0.5*(sin(5*time+1.0)+1.0),
                                            0.5*(sin(5*time+2.0)+1.0),
                                            1.0);
}
