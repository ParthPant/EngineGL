#pragma once
#include <glad/glad.h>

class Sprite{
public:
    Sprite();
    ~Sprite();

    void draw();
    void init(float x, float y, float width, float height);
private:
    float _x;
    float _y;
    float _width;
    float _height;

    GLuint _vboID;
};
