#include "VertexArray.h"
#include "Log.h"
#include <memory>

namespace Engine{

VertexArray::VertexArray()
{
}

VertexArray::~VertexArray()
{
}

void VertexArray::bind()
{
    glBindVertexArray(_id);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

std::shared_ptr<VertexArray> VertexArray::create()
{
    std::shared_ptr<VertexArray> va = std::make_shared<VertexArray>();
    glGenVertexArrays(1, &(va->_id)); 
    glBindVertexArray(va->_id);
    
    return va;
}

void VertexArray::addVertexBuffer(std::shared_ptr<VertexBuffer>& vb)
{
    glBindVertexArray(_id);
    vb->bind();
    _vb = vb;

    std::shared_ptr<VertexLayout> layout = vb->getLayout();
    int i=0;
    for(auto element : *layout)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i
                             ,element.count
                             ,getGlType(element.type)
                             ,element.normalized ? GL_TRUE : GL_FALSE
                             ,layout->getStride()
                             ,(const void*)element.offset);
        i++;
    }
    _layout = layout;
    glBindVertexArray(0);
}

void VertexArray::addElementBuffer(std::shared_ptr<ElementBuffer>& eb)
{
    glBindVertexArray(_id);
    eb->bind();
    _eb = eb;
    glBindVertexArray(0);
}

}
