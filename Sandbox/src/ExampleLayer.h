#pragma once

#include "Camera2D.h"
#include "Events/Events.hpp"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "Layers.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexLayout.h"
#include <string>

enum class GameState{
    PLAY,
    EXIT
};

class ExampleLayer : public Engine::Layer
{
public:
    ExampleLayer(std::string const &name)
        :Layer(name)
    {
    }
    
    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onEvent(Engine::Event& e) override;
    void onImGuiRender() override;

private:

    std::shared_ptr<Engine::VertexBuffer> _vbo;
    std::shared_ptr<Engine::ElementBuffer> _ibo;
    std::shared_ptr<Engine::VertexArray> _vao;
    std::shared_ptr<Engine::VertexLayout> _layout;
    std::shared_ptr<Engine::GLSLProgram> _shader;
    std::unique_ptr<Engine::Renderer> _renderer;
    std::shared_ptr<Engine::OrthographicCamera> _camera;

    float _transform[3];
};

