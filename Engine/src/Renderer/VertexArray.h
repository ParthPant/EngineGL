#pragma once

#include "Renderer/ElementBuffer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexLayout.h"
#include <memory>
#include <stdint.h>

namespace Engine{

class VertexArray{
public:
    ~VertexArray();

    void addVertexBuffer(VertexBuffer* vb);
    void addElementBuffer(ElementBuffer* eb);

    void bind();
    void unbind();

    uint32_t getId() {return _id;}

    static VertexArray* create();
private:
    VertexArray();
    uint32_t _id; 

    VertexBuffer* _vb;
    VertexLayout* _layout;
    ElementBuffer* _eb;
};

}
