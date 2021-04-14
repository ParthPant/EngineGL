#include <iostream>

#include "GLTexture.h"
#include "MainGame.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
#include "SDL_events.h"
#include "Sprite.h"
#include "Window.h"
#include "Camera2D.h"
#include "GLSLProgram.h"
#include "Log.h"
#include "Engine.h"
#include "fwd.hpp"

MainGame::MainGame()
    :_gameState(GameState::PLAY)
    ,_time(0)
    ,_screenWidth(1024)
    ,_screenHeight(768)
    ,_maxFps(60.0f)
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

void MainGame::initShaders()
{
    _program.compileShaders("/home/parth/dev/opengl/Sandbox/res/shaders/colorshading.vert"
                           ,"/home/parth/dev/opengl/Sandbox/res/shaders/colorshading.frag");
    _program.addAttribute("vertexPosition");
    _program.addAttribute("vertexColor");
    _program.addAttribute("vertexUV");
    _program.linkShaders();
}

void MainGame::initSystems()
{
    Engine::Log::init();
    Engine::init();
    _camera.init(_screenWidth, _screenHeight);
    _window.createWindow("Sandbox", _screenWidth, _screenHeight, 0);
    initShaders();
    glClearColor(0, 0, 1, 1.0);
    _texture = Engine::ResourceManager::getTexture("/home/parth/dev/opengl/Sandbox/res/textures/ethereum.png");
    _spritebatch.init();
    _fpslimiter.init(_maxFps);
}

void MainGame::processInput()
{
    SDL_Event event;

    const float cam_speed = 20.0f;
    const float scale_speed = 0.1f;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_KEYDOWN:
                _inputmanager.pressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputmanager.releaseKey(event.key.keysym.sym);
        }
    }
    
    if (_inputmanager.isKeyPressed(SDLK_w))
        _camera.setPosition(_camera.getPosition()+glm::vec2(0, cam_speed));

    if (_inputmanager.isKeyPressed(SDLK_s))
        _camera.setPosition(_camera.getPosition()+glm::vec2(0, -cam_speed));

    if (_inputmanager.isKeyPressed(SDLK_a))
        _camera.setPosition(_camera.getPosition()+glm::vec2(-cam_speed, 0));

    if (_inputmanager.isKeyPressed(SDLK_d))
        _camera.setPosition(_camera.getPosition()+glm::vec2(cam_speed, 0));

    if (_inputmanager.isKeyPressed(SDLK_q))
        _camera.setScale(_camera.getScale() + scale_speed);

    if (_inputmanager.isKeyPressed(SDLK_e))
        _camera.setScale(_camera.getScale() - scale_speed);
}

void MainGame::drawGame()
{
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program.bind();

    glActiveTexture(GL_TEXTURE0);
    GLint sampler = _program.getUniformLocation("sampler");
    glUniform1i(sampler, 0); 

    GLint mat = _program.getUniformLocation("P");
    glUniformMatrix4fv(mat, 1, GL_FALSE, &(_camera.getCamMatrix()[0][0]));

    _spritebatch.begin();

    int n = 10;

    float width = _screenWidth/n;
    float height = _screenHeight/n;

    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
        {
            float x = ((float)i/(float)n -                     1) * (float)_screenWidth + (float)_screenWidth/2;
            float y = (1                 - (float)(j+1)/(float)n) * (float)_screenHeight - (float)_screenHeight/2;

            _spritebatch.draw(glm::vec4(x, y, width, height)
                             ,glm::vec4(0,0,1,1)
                             ,0
                             ,_texture.id
                             ,{255,255,255,255});
        }

    _spritebatch.end();
    _spritebatch.renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);
    _program.unbind();
    
    _window.swapBuffers();
}

void MainGame::gameLoop()
{
    while (_gameState == GameState::PLAY) {
        _fpslimiter.begin();

        processInput();
        _camera.update();
        drawGame();

        //limit fps to _maxFps
        _fpslimiter.end();

        //print fps every 50 frames
        static int frame_counter = 0;
        frame_counter ++;
        _fps = _fpslimiter.getFPS();
        if (frame_counter % 50 == 0)
        {
            Engine::TRACE("FPS: {}", _fps);
            frame_counter = 0;
        }
    }
}

