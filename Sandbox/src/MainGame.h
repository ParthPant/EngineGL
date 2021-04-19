#pragma once

#include "GLTexture.h"
#include "Sprite.h"
#include "Camera2D.h"
#include "GLSLProgram.h"
#include "Window.h"
#include "InputManager.h"
#include "SpriteBatch.h"
#include "Timing.h"
#include "Engine.h"

#include <vector>

enum class GameState{
    PLAY,
    EXIT
};

class MainGame : public Engine::Application{
public:
    MainGame();
    ~MainGame();

    void run() override;

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();
    void calculateFps();

    int _screenWidth = 1024;
    int _screenHeight = 768;

    GameState _gameState;
    Engine::GLTexture _texture;
    Engine::GLTexture _texture2;
    Engine::GLSLProgram _program;
    Engine::Camera2D _camera;
    Engine::SpriteBatch _spritebatch;
    Engine::InputManager _inputmanager;
    Engine::FPSLimiter _fpslimiter;

    float _time;
    float _fps;
    float _frameTime;
    float _maxFps;

    int n = 5;
};
