#include "Application.h"
#include "Events/Events.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "SDL.h"
#include "Events/ApplicationEvent.hpp"
#include "Log.h"

#include "SDL_events.h"
#include "glad/glad.h"

#include <memory>
#include <functional>

namespace Engine{

Application* Application::_app;

Application::Application(std::string const & name)
    :_running(true)
    ,_name(name)
{
    _app = this;
    _window = new Window();
    _window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    _window->createWindow(_name, 1280, 1024, 0);
    glClearColor(52.0f/225.0f, 57/225.0f, 77/225.0f, 1.0);
}

void Application::run()
{
    while(_running)
    {
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto *layer : _layers)
        {
            layer->onUpdate();
        }

        _window->onUpdate();
    }
}

Application::~Application()
{
    delete(_window);
    delete(_app);
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
