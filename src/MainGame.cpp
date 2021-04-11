#include <iostream>

#include "MainGame.h"
#include "Sprite.h"
#include "GLSLProgram.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_video.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

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

    _sprite.init(-1, -1, 1, 1);

    gameLoop();
}

void MainGame::initShaders()
{
    _program.compileShaders("/home/parth/dev/opengl/res/shaders/colorshading.vert","/home/parth/dev/opengl/res/shaders/colorshading.frag");
    _program.addAttribute("vertexPosition");
    _program.linkShaders();
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
        spdlog::error("SDL failed to create a window");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);

    if (!glContext) {
        spdlog::error("GLContext could not be created");
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        spdlog::error("Glad was unable to load");
    }

    spdlog::info("OpenGL version: {}", glGetString(GL_VERSION));
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    initShaders();
    glClearColor(0, 0, 1, 1.0);
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

void MainGame::drawGame()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program.bind();
    _sprite.draw();
    _program.unbind();

    SDL_GL_SwapWindow(_window);
}

void MainGame::gameLoop()
{
    while (_gameState == GameState::PLAY) {
        processInput();
        drawGame();
    }
}
