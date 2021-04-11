#include <iostream>

#include "MainGame.h"
#include "ImageLoader.h"
#include "Sprite.h"
#include "GLSLProgram.h"
#include "SDL.h"
#include "glad/glad.h"
#include "Log.h"

MainGame::MainGame()
    :_window(nullptr)
    ,_gameState(GameState::PLAY)
    ,_time(0)
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
    initSystems();    
    _sprite.init(0, 0, 0.5, 0.5);
    _texture = ImageLoader::loadPng("/home/parth/dev/opengl/res/textures/wood.png");
    _texture2 = ImageLoader::loadPng("/home/parth/dev/opengl/res/textures/concrete.png");
    gameLoop();
}

void MainGame::initShaders()
{
    _program.compileShaders("/home/parth/dev/opengl/res/shaders/colorshading.vert"
                           ,"/home/parth/dev/opengl/res/shaders/colorshading.frag");
    _program.addAttribute("vertexPosition");
    _program.addAttribute("vertexColor");
    _program.addAttribute("vertexUV");
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
        ERROR("SDL failed to create a window");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);

    if (!glContext) {
        ERROR("GLContext could not be created");
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        ERROR("Glad was unable to load");
    }

    Log::init();

    INFO("OpenGL version: {}", glGetString(GL_VERSION));
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    initShaders();
    glClearColor(1, 1, 1, 1.0);
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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.id);
    GLint texture = _program.getUniformLocation("sampler");
    glUniform1i(texture, 0); 

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _texture2.id);
    texture = _program.getUniformLocation("sampler2");
    glUniform1i(texture, 1); 

    _sprite.draw();

    glBindTexture(GL_TEXTURE_2D, 0);
    _program.unbind();

    SDL_GL_SwapWindow(_window);
}

void MainGame::gameLoop()
{
    while (_gameState == GameState::PLAY) {
        processInput();
        drawGame();
        _time += 0.01;
    }
}
