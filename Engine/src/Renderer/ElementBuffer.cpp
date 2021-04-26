#include "ElementBuffer.h"
#include "glad/glad.h"
#include <memory>

namespace Engine{

ElementBuffer::ElementBuffer()
{
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &_id);
}

std::shared_ptr<ElementBuffer> ElementBuffer::create()
{
    std::shared_ptr<ElementBuffer> eb = std::make_shared<ElementBuffer>();
    glGenBuffers(1, &(eb->_id));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb->_id);
    return eb;
}

void ElementBuffer::setData(unsigned int *indices, uint32_t size)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
    _num_vertices = size/sizeof(unsigned int);
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
