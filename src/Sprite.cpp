#include "Sprite.h"

Sprite::Sprite()
    :_vboID(0)
{
}

Sprite::~Sprite()
{
    if (_vboID) {
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::init(float x, float y, float width, float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    if (!_vboID) {
        glGenBuffers(1, &_vboID);
    }
    
    float vertexData[12];
    vertexData[0] = x + width;
    vertexData[1] = y + height;

    vertexData[2] = x - width;
    vertexData[3] = y + height;

    vertexData[4] = x - width;
    vertexData[5] = y - height;

    vertexData[6] = x - width;
    vertexData[7] = y - height;

    vertexData[8] = x + width;
    vertexData[9] = y - height;

    vertexData[10] = x + width;
    vertexData[11] = y + height;

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), (void*)vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
