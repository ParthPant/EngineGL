#pragma once

#include "SDL.h"

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
    void gameLoop();
    void processInput();

    SDL_Window* _window;
    int _screenWidth = 1024;
    int _screenHeight = 768;

    GameState _gameState;
};
