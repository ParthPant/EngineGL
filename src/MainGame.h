#pragma once

#include "GLTexture.h"
#include "SDL.h"
#include "Sprite.h"
#include "GLSLProgram.h"

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

    SDL_Window* _window;
    int _screenWidth = 1024;
    int _screenHeight = 768;

    GameState _gameState;
    Sprite _sprite;
    GLTexture _texture;
    GLTexture _texture2;
    GLSLProgram _program;

    float _time;
};
