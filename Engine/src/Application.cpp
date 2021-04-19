#include "Application.h"
#include "Events/Events.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "SDL.h"
#include "Events/ApplicationEvent.hpp"
#include "Log.h"
#include <memory>
#include <functional>

namespace Engine{

Application::Application()
{
    //_window.setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
    _window.setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
}

void Application::run()
{
}

Application::~Application()
{
}

void Application::onEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>([](Event &e)->bool
            {
                TRACE(e.toString());
                SDL_Quit();
                exit(0);
                return true;
            });
    dispatcher.dispatch<WindowResizeEvent>([](Event &e)->bool
            {
                TRACE(e.toString());
                return true;
            });
    dispatcher.dispatch<KeyPressedEvent>([](Event &e)->bool
            {
                TRACE(e.toString());
                return true;
            });
}

}
