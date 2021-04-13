#include <iostream>

#include "GLTexture.h"
#include "MainGame.h"
#include "ImageLoader.h"
#include "ResourceManager.h"
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
    _window.createWindow("Sandbox", _screenWidth, _screenHeight, Engine::FULLSCREEN);
    initShaders();
    glClearColor(1, 1, 1, 1.0);
    _spritebatch.init();
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
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        _camera.setPosition(_camera.getPosition()+glm::vec2(0, cam_speed));
                        break;
                    case SDLK_s:
                        _camera.setPosition(_camera.getPosition()+glm::vec2(0, -cam_speed));
                        break;
                    case SDLK_a:
                        _camera.setPosition(_camera.getPosition()+glm::vec2(-cam_speed, 0));
                        break;
                    case SDLK_d:
                        _camera.setPosition(_camera.getPosition()+glm::vec2(cam_speed, 0));
                        break;
                    case SDLK_q:
                        _camera.setScale(_camera.getScale() + scale_speed);
                        break;
                    case SDLK_e:
                        _camera.setScale(_camera.getScale() - scale_speed);
                        break;
                }
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
    GLint sampler = _program.getUniformLocation("sampler");
    glUniform1i(sampler, 0); 

    GLint mat = _program.getUniformLocation("P");
    glUniformMatrix4fv(mat, 1, GL_FALSE, &(_camera.getCamMatrix()[0][0]));

    GLint time = _program.getUniformLocation("time");
    glUniform1f(time, _time);

    _spritebatch.begin();

    Engine::GLTexture texture = Engine::ResourceManager::getTexture("/home/parth/dev/opengl/Sandbox/res/textures/sprite.png");

    int n = 20;

    float width = _screenWidth/n;
    float height = _screenHeight/n;

    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
        {
            float x = ((float)i/(float)n -                     1) * (float)_screenWidth + (float)_screenWidth/2;
            float y = (1                 - (float)(j+1)/(float)n) * (float)_screenHeight - (float)_screenHeight/2;

            _spritebatch.draw(glm::vec4(x, y, width, height)
                             ,glm::vec4(0,0,4,1)
                             ,0
                             ,texture.id
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
        float startTicks = SDL_GetTicks();

        processInput();
        _camera.update();
        drawGame();

        _time += 0.01;
        calculateFps();

        //print fps every 50 frames
        static int frame_counter = 0;
        frame_counter ++;
        if (frame_counter % 50 == 0)
        {
            Engine::TRACE("FPS: {}", _fps);
            frame_counter = 0;
        }

       //limit fps to _maxFps
       float frameTicks = startTicks - SDL_GetTicks();
       if (1000.0f / _maxFps > frameTicks)
           SDL_Delay(1000.0f/_maxFps - frameTicks);
    }
}

void MainGame::calculateFps()
{
    static const int NUM_SAMPLES = 100;
    static float frame_times[NUM_SAMPLES];
    static float prev_tics = SDL_GetTicks();
    static int curr_frame = 0;

    float current_tics =  SDL_GetTicks();

    _frameTime = current_tics - prev_tics;

    frame_times[curr_frame % NUM_SAMPLES] = _frameTime;

    int count = curr_frame < NUM_SAMPLES ? curr_frame : NUM_SAMPLES;
    
    float frame_time_avg = 0;
    for (int i=0; i<count; i++)
        frame_time_avg += frame_times[i];

    frame_time_avg = count > 0 ? frame_time_avg/count : 0;
    _fps = frame_time_avg > 0 ? 1000.0f/frame_time_avg : 0;

    prev_tics = current_tics;
    curr_frame++;
}
