#pragma once

#include "GLSLProgram.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/VertexArray.h"
#include "glm.hpp"
#include <memory>

namespace Engine{

class RenderCommand{
public:
    static void ClearColor(glm::vec4 const &color);
    static void Clear();
};

class Renderer{
public:
    Renderer()
    {
    }
    //~Renderer();

    void beginScene(std::shared_ptr<OrthographicCamera>& camera);
    void submit(std::shared_ptr<GLSLProgram>& shader, std::shared_ptr<VertexArray>& vao);
    void endScene();

private:
    std::shared_ptr<VertexArray> _vao;
    std::shared_ptr<OrthographicCamera> _camera;
    std::shared_ptr<GLSLProgram> _shader;
};

}
