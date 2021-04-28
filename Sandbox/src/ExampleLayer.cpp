#include "ExampleLayer.h"
#include "Application.h"
#include "Engine.h"
#include "Events/Events.hpp"
#include "Events/KeyEvent.hpp"
#include "GLTexture.h"
#include "Log.h"
#include "SDL_keycode.h"
#include "imgui.h"
#include "InputManager.h"
#include <memory>

void ExampleLayer::onAttach()
{
    float vertices[] = {
       -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
        0,1,2,
        0,1,3
    };

    _layout.reset( new Engine::VertexLayout({{Engine::ShaderDataType::Float3, "Position"}
                                    ,{Engine::ShaderDataType::Float4, "Color"}
                                    }));
                 
    _vbo = Engine::VertexBuffer::create();
    _vbo->setData(vertices, sizeof(vertices));
    _vbo->setLayout(_layout);

    _ibo = Engine::ElementBuffer::create();
    _ibo->setData(indices, sizeof(indices));

    _vao = Engine::VertexArray::create();
    _vao->addVertexBuffer(_vbo);
    _vao->addElementBuffer(_ibo);

    _shader = std::make_shared<Engine::GLSLProgram>();
    _shader->compileShaders("/home/parth/dev/opengl/Sandbox/res/shaders/simpleshader.vert",
                            "/home/parth/dev/opengl/Sandbox/res/shaders/simpleshader.frag");
    _shader->linkShaders();
    _vao->unbind();

    _renderer = std::make_unique<Engine::Renderer>();
    _camera = std::make_shared<Engine::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);
    _camera->setPosition({0, 0, 0});
}

void ExampleLayer::onUpdate()
{
    _renderer->beginScene(_camera);
    _renderer->submit(_shader, _vao, glm::translate(glm::mat4(1.0f), {_transform[0], _transform[1], _transform[2]}));
    _renderer->endScene();
}

void ExampleLayer::onDetach()
{
}

void ExampleLayer::onEvent(Engine::Event &e)
{
}

void ExampleLayer::onImGuiRender()
{
    ImGui::Begin("Transform");
    ImGui::DragFloat3("position", _transform, 0.1f);
    ImGui::End();
}
