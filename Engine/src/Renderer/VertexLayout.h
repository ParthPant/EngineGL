#pragma once

#include "glad/glad.h"
#include <string>
#include <vector>

namespace Engine{

enum class ShaderDataType{
    NONE=0, Int,
    Int2,
    Int3,
    Int4,
    Float,
    Float2,
    Float3,
    Float4,
    Mat2,
    Mat3,
    Mat4,
    Bool
};

static GLenum getGlType(ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::NONE:   return 0;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat2:   return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        case ShaderDataType::Bool:   return GL_BOOL;
    }
    return 0;
}

static uint32_t getCount(ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::NONE:   return 0;
        case ShaderDataType::Float:  
        case ShaderDataType::Int:    return 1;
        case ShaderDataType::Float2:
        case ShaderDataType::Int2:   return 2;
        case ShaderDataType::Float3: 
        case ShaderDataType::Int3:   return 3;
        case ShaderDataType::Float4: 
        case ShaderDataType::Int4:   return 4;
        case ShaderDataType::Mat2:   return 2*2;
        case ShaderDataType::Mat3:   return 4*3;
        case ShaderDataType::Mat4:   return 4*4;
        case ShaderDataType::Bool:   return 1;
    }
    return 0;
}

static uint32_t getSize(ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::NONE:   return 0;
        case ShaderDataType::Float:  
        case ShaderDataType::Int:    return 4;
        case ShaderDataType::Float2:
        case ShaderDataType::Int2:   return 4*2;
        case ShaderDataType::Float3: 
        case ShaderDataType::Int3:   return 4*3;
        case ShaderDataType::Float4: 
        case ShaderDataType::Int4:   return 4*4;
        case ShaderDataType::Mat2:   return 4*2*2;
        case ShaderDataType::Mat3:   return 4*3*3;
        case ShaderDataType::Mat4:   return 4*4*4;
        case ShaderDataType::Bool:   return 1;
    }
    return 0;
}

struct VertexElement{
    ShaderDataType type;
    uint32_t size;
    uint32_t count;
    uint32_t offset;
    bool normalized;
    std::string name;

    VertexElement(ShaderDataType ptype, std::string const &pname, bool pmormalized = false)
        :type(ptype)
        ,size(getSize(ptype))
        ,count(getCount(ptype))
        ,offset(0)
        ,normalized(pmormalized)
        ,name(pname)
    {
    }
};


class VertexLayout{
public:
    VertexLayout(std::vector<VertexElement> const &layout)
        :_layout(layout)
    {
        caculateOffsetAndStride();
    }

    VertexLayout()
    {
    }

    ~VertexLayout();

    std::vector<VertexElement>::iterator begin() {return _layout.begin();}
    std::vector<VertexElement>::iterator end() {return _layout.end();}

    std::vector<VertexElement>::const_iterator begin() const {return _layout.begin();}
    std::vector<VertexElement>::const_iterator end() const {return _layout.end();}

    int getStride() const {return _stride;}
    
private:
    void caculateOffsetAndStride();
    uint32_t _stride = 0;
    std::vector<VertexElement> _layout;
};

}
