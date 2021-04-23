#include "VertexLayout.h"

namespace Engine{

VertexLayout::~VertexLayout()
{
}

void VertexLayout::caculateOffsetAndStride()
{
    uint32_t offset = 0;
    for(auto &element : _layout)
    {
        element.offset = offset;
        offset += element.size;
    }
    _stride = offset;
}

}
