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
    VertexArray();

    void addVertexBuffer(std::shared_ptr<VertexBuffer>& vb);
    void addElementBuffer(std::shared_ptr<ElementBuffer>& eb);

    void bind();
    void unbind();

    uint32_t getId() {return _id;}
    std::shared_ptr<ElementBuffer> getElementBuffer() {return _eb;}

    static std::shared_ptr<VertexArray> create();
private:
    uint32_t _id; 

    std::shared_ptr<VertexBuffer> _vb;
    std::shared_ptr<VertexLayout> _layout;
    std::shared_ptr<ElementBuffer> _eb;
};

}
