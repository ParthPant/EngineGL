#pragma once

#include "GLSLProgram.h"
#include "Layers.h"
#include "Window.h"
#include "ImGuiLayer.h"
#include "Timing.h"
#include <memory>

namespace Engine{

class Application{
public:
    virtual ~Application();

    virtual void run();
    void onEvent(Event &e);

    void pushLayer(Layer* l)
    {
        _layers.push(l);
        l->onAttach();
    }
    void pushOverlay(Layer* l)
    {
        _layers.addOverlay(l);
        l->onAttach();
    }

    Window* getWindow() const {return _window.get();}
    static Application* getApplication() { return _app.get(); }

protected:
    Application(std::string const & name);

    std::unique_ptr<Window> _window;
    static std::unique_ptr<Application> _app;
    std::string _name;

    std::unique_ptr<FPSLimiter> _fpslimiter;

    ImGuiLayer* _imGuiLayer;
    LayerStack _layers;
    bool _running;
};

Application* CreateApplication();
}


