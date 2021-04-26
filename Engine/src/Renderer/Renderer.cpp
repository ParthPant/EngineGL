#include "Renderer.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/VertexArray.h"
#include "glm.hpp"
#include "glad/glad.h"
#include <memory.h>

namespace Engine{

void RenderCommand::ClearColor(glm::vec4 const &color)
{
    glClearColor(color.x, color.y, color.x, color.w);
}

void RenderCommand::Clear()
{
    glClearDepth(1.0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Renderer::beginScene(std::shared_ptr<OrthographicCamera>& camera)
{
    _camera = camera;
}

void Renderer::submit(std::shared_ptr<GLSLProgram>& shader, std::shared_ptr<VertexArray>& vao)
{
    _shader = shader;
    _shader->bind();

    _shader->uploadUniformMat4("ViewProjection", _camera->getProjectionMatrix());

    _vao = vao;
    _vao->bind();
    glDrawElements(GL_TRIANGLES, _vao->getElementBuffer()->getNumVertices(), GL_UNSIGNED_INT, 0);
}

void Renderer::endScene()
{
}

}
