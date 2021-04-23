#pragma once

#include "GLSLProgram.h"
#include "Layers.h"
#include "Renderer/ElementBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexLayout.h"
#include "Window.h"
#include "ImGuiLayer.h"
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

    Window* getWindow() {return _window;}

    static Application* getApplication(){ return _app; }
protected:
    Application(std::string const & name);

    Window* _window;
    static Application *_app;
    std::string _name;

    ImGuiLayer* _imGuiLayer;
    LayerStack _layers;
    bool _running;

    VertexBuffer* _vbo;
    VertexLayout* _layout;
    ElementBuffer* _ibo;
    VertexArray* _vao;

    GLSLProgram _program;
};

Application* CreateApplication();
}


