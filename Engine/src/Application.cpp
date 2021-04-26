#include "Application.h"
#include "GLSLProgram.h"
#include "ImGuiLayer.h"
#include "Events/Events.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Renderer/Renderer.h"
#include "SDL.h"
#include "Log.h"
#include "SDL_events.h"

#include <memory>
#include <functional>

namespace Engine{

std::unique_ptr<Application> Application::_app;

Application::Application(std::string const & name)
    :_running(true)
    ,_name(name)
{
    _app.reset(this);
    _window = std::make_unique<Window>();
    _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    _window->createWindow(_name, 1280, 720, 0);
    _fpslimiter = std::make_unique<FPSLimiter>();
    _fpslimiter->setTargetFPS(60.0f);
    RenderCommand::ClearColor({0.1f, 0.1f, 0.1f, 1.0f});

    _imGuiLayer = new ImGuiLayer();
    pushOverlay(_imGuiLayer);
}

void Application::run()
{
    while(_running)
    {
        _fpslimiter->begin();
        _window->processInput();
    
        RenderCommand::Clear();

        for (auto *layer : _layers)
            layer->onUpdate();

        _imGuiLayer->imGuiBegin();

        for(auto *layer : _layers)
            layer->onImGuiRender();

        _imGuiLayer->imGuiEnd();

        _window->swapBuffers();
        _fpslimiter->end();
    }
}

Application::~Application()
{
}

void Application::onEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>([this](Event &e)->bool
            {
                this->_running = false;
                SDL_Quit();
                exit(0);
                return true;
            });

    for (auto it = _layers.end(); it != _layers.begin();)
    {
        (*--it)->onEvent(e);
        if (e.isHandled())
            break;
    }
}

}
