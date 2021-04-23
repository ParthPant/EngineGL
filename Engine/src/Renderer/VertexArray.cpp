#include "VertexArray.h"
#include "Log.h"

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

VertexArray* VertexArray::create()
{
    VertexArray* va = new VertexArray();
    glGenVertexArrays(1, &(va->_id)); 
    glBindVertexArray(va->_id);
    
    return va;
}

void VertexArray::addVertexBuffer(VertexBuffer* vb)
{
    glBindVertexArray(_id);
    vb->bind();
    _vb = vb;

    VertexLayout* layout = vb->getLayout();
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

void VertexArray::addElementBuffer(ElementBuffer* eb)
{
    glBindVertexArray(_id);
    eb->bind();
    _eb = eb;
    glBindVertexArray(0);
}

}
