#pragma once

#include "GLTexture.h"
#include "SDL.h"
#include "Sprite.h"
#include "GLSLProgram.h"
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

    SDL_Window* _window;
    int _screenWidth = 1024;
    int _screenHeight = 768;

    GameState _gameState;
    std::vector<Sprite *> _sprites;
    GLTexture _texture;
    GLSLProgram _program;

    float _time;
    float _fps;
    float _frameTime;
    float _maxFps;
};
