#pragma once

#include "GLTexture.h"
#include "SDL.h"
#include "Sprite.h"
#include "GLSLProgram.h"
#include "Window.h"
#include <vector>

enum class GameState{
    PLAY,
    EXIT
};

class MainGame{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();
    void calculateFps();

    Engine::Window _window;
    int _screenWidth = 1024;
    int _screenHeight = 768;

    GameState _gameState;
    std::vector<Engine::Sprite *> _sprites;
    Engine::GLTexture _texture;
    Engine::GLSLProgram _program;

    float _time;
    float _fps;
    float _frameTime;
    float _maxFps;
};
