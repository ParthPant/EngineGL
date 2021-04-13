#version 330 core 

out vec4 color;

in vec4 vertColor;
in vec2 vertUV;
in vec2 vertPos;

uniform sampler2D sampler;
uniform float time;

void main() {
    vec4 textureColor = texture(sampler, vertUV);
    color = vertColor * textureColor * vec4(0.5*(vertColor.x + (sin(time+vertPos.x)+1)*0.5)
                                           ,0.5*(vertColor.y + (sin(time+vertPos.y)+1)*0.5)
                                           ,0.5*(vertColor.z + (sin(time)          +1)*0.5)
                                           ,1.0); 
}
