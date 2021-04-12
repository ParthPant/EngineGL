#include <iostream>

#include "MainGame.h"
#include "ImageLoader.h"
#include "Sprite.h"
#include "Window.h"
#include "GLSLProgram.h"
#include "Log.h"
#include "Engine.h"

MainGame::MainGame()
    :_gameState(GameState::PLAY)
    ,_time(0)
    ,_maxFps(60.0f)
{
}

MainGame::~MainGame()
{
    for (auto *s : _sprites)
        delete(s);

    _sprites.clear();
}

void MainGame::run()
{
    initSystems();    

    for (int i=0; i<2; i++)
        _sprites.push_back(new Engine::Sprite());

    for (int i = 0; i < _sprites.size(); i++)
        _sprites[i]->init(-0.5+i, 0.5, 0.5, 0.5, "/home/parth/dev/opengl/Sandbox/res/textures/wood.png");

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
    _window.createWindow("Sandbox", _screenWidth, _screenHeight, Engine::FULLSCREEN);
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
    GLint sampler = _program.getUniformLocation("sampler");
    glUniform1i(sampler, 0); 

    GLint time = _program.getUniformLocation("time");
    glUniform1f(time, _time);

    for (Engine::Sprite *s : _sprites)
        s->draw();

    glBindTexture(GL_TEXTURE_2D, 0);
    _program.unbind();
    
    _window.swapBuffers();
}

void MainGame::gameLoop()
{
    while (_gameState == GameState::PLAY) {
        float startTicks = SDL_GetTicks();

        processInput();
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
