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

    void setData(unsigned int *indices, uint32_t size);

private:

    uint32_t _id;
};

}
