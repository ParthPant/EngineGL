#pragma once

#include "VertexLayout.h"
#include "glad/glad.h"

namespace Engine{


class VertexBuffer{
public:
    ~VertexBuffer();

    void bind();
    void unbind();
    void setData(float *vertices, int size);
    void setLayout(VertexLayout *layout) {_layout = layout;}
    VertexLayout* getLayout() {return _layout;}

    int getId() {return _vbo;}
    static VertexBuffer* create();

private:

    VertexBuffer();

    VertexLayout *_layout;
    GLuint _vbo;
};

}
