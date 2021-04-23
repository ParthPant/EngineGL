#pragma once

#include "Camera2D.h"
#include "Events/Events.hpp"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "Layers.h"
#include "Application.h"
#include "SpriteBatch.h"
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
        ,_texture(0, 0, 0)
    {
    }
    
    void onAttach() override;
    void onDetach() override;
    void onUpdate() override;
    void onEvent(Engine::Event& e) override;
    void onImGuiRender() override;

private:
    Engine::GLSLProgram _program;
    Engine::SpriteBatch _spriteBatch;
    Engine::GLTexture _texture;
    Engine::Camera2D _camera;

    float _positionx = 0;
};

