#include <iostream>

#include "MainGame.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"
#include "glad/glad.h"

MainGame::MainGame()
    :_window(nullptr),
    _gameState(GameState::PLAY)
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
    initSystems();    
    gameLoop();
}

void MainGame::initSystems()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("Game",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               _screenWidth,
                               _screenHeight,
                               SDL_WINDOW_OPENGL);

    if (!_window) {
        //error
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);

    if (!glContext) {
        //error
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout<<"Unable to load glad"<<std::endl;
    }
}

void MainGame::processInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                break;
        }
    }
}

void MainGame::gameLoop()
{
    while (_gameState == GameState::PLAY) {
        processInput();
    }
}
