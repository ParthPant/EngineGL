#pragma once

#include "Window.h"

namespace Engine{

class Application{
public:
    Application();
    virtual ~Application();

    virtual void run();
    void onEvent(Event &e);
protected:
    Window _window;
};

Application* CreateApplication();

}


