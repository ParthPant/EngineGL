#pragma once

#include <stdint.h>
#include <memory>

namespace Engine{

class ElementBuffer{
public:
    ~ElementBuffer();
    ElementBuffer();

    static std::shared_ptr<ElementBuffer> create();

    void bind();
    void unbind();
    uint32_t getId() {return _id;}
    int getNumVertices() {return _num_vertices;}

    void setData(unsigned int *indices, uint32_t size);

private:

    int _num_vertices = 0;
    uint32_t _id;
};

}
