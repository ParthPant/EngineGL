#include "VertexBuffer.h"
#include "Log.h"
#include "glad/glad.h"
#include <memory>
#include <stdint.h>

namespace Engine{

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_vbo);
}

std::shared_ptr<VertexBuffer> VertexBuffer::create()
{
    std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>();

    glGenBuffers(1, &(vb->_vbo));
    glBindBuffer(GL_ARRAY_BUFFER, vb->_vbo);

    return vb;
}

void VertexBuffer::setData(float *vertices, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}
    
void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}
