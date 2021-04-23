#include "ElementBuffer.h"
#include "glad/glad.h"

namespace Engine{

ElementBuffer::ElementBuffer()
{
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &_id);
}

ElementBuffer* ElementBuffer::create()
{
    ElementBuffer* eb = new ElementBuffer();
    glGenBuffers(1, &(eb->_id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb->_id);
    return eb;
}

void ElementBuffer::setData(unsigned int *indices, uint32_t size)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
}

void ElementBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void ElementBuffer::unbind()
{
    glBindVertexArray(0);
}

}
