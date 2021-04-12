#pragma once

#include "GLTexture.h"
#include <glad/glad.h>
#include <string>

namespace Engine{

struct Vertex{
    struct Postition
    {
        float x;
        float y;
    } position;

    struct Color
    {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    }color;

    struct UV
    {
        float u = 1;
        float v = 1;
    }uv;

    void setPosition(float x, float y){ 
        position.x = x;
        position.y = y;
    }

    void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255){
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void setUV(float u, float v){
        uv.u = u;
        uv.v = v;
    }
};

class Sprite{
public:
    Sprite();
    ~Sprite();

    void draw();
    void init(float x, float y, float width, float height, std::string const &texture_path = "");
private:
    float _x;
    float _y;
    float _width;
    float _height;

    GLTexture _texture;

    GLuint _vboID;
};

}
