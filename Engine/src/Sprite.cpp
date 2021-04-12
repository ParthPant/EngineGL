#include "Sprite.h"
#include "ResourceManager.h"
#include <cstddef>

namespace Engine{

Sprite::Sprite()
    :_vboID(0)
    ,_texture({0,0,0})
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    if (_texture.id)
        glBindTexture(GL_TEXTURE_2D, _texture.id);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::init(float x, float y, float width, float height, std::string const &texture_path)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    if (!_vboID) {
        glGenBuffers(1, &_vboID);
    }
    
    Vertex vertexData[6];
    vertexData[0].setPosition(x+width, y+height);
    vertexData[1].setPosition(x-width, y+height);
    vertexData[2].setPosition(x-width, y-height);
    vertexData[3].setPosition(x-width, y-height);
    vertexData[4].setPosition(x+width, y-height);
    vertexData[5].setPosition(x+width, y+height);

    vertexData[0].setColor(0, 0, 255);
    vertexData[1].setColor(0, 255, 0);
    vertexData[2].setColor(255, 0, 0);
    vertexData[3].setColor(255, 0, 0);
    vertexData[4].setColor(255, 255, 255);
    vertexData[5].setColor(0, 0, 255);

    vertexData[0].setUV(1.0, 1.0);
    vertexData[1].setUV(0.0, 1.0);
    vertexData[2].setUV(0.0, 0.0);
    vertexData[3].setUV(0.0, 0.0);
    vertexData[4].setUV(1.0, 0.0);
    vertexData[5].setUV(1.0, 1.0);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), (void*)vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (!texture_path.empty())
        _texture = ResourceManager::getTexture(texture_path);
}

}
