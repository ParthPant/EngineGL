#pragma once

#include "VertexLayout.h"
#include "glad/glad.h"

#include <memory>

namespace Engine{


class VertexBuffer{
public:
    ~VertexBuffer();
    VertexBuffer();

    void bind();
    void unbind();
    void setData(float *vertices, int size);
    void setLayout(std::shared_ptr<VertexLayout>& layout) {_layout = layout;}
    std::shared_ptr<VertexLayout> getLayout() {return _layout;}

    int getId() {return _vbo;}
    static std::shared_ptr<VertexBuffer> create();

private:
    std::shared_ptr<VertexLayout> _layout;
    GLuint _vbo;
};

}
