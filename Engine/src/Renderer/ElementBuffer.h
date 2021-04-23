#pragma once

#include <stdint.h>

namespace Engine{

class ElementBuffer{
public:
    ~ElementBuffer();

    static ElementBuffer* create();

    void bind();
    void unbind();
    uint32_t getId() {return _id;}

    void setData(unsigned int *indices, uint32_t size);

private:
    ElementBuffer();

    uint32_t _id;
};

}
