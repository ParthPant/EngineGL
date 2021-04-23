#include "Application.h"
#include "GLSLProgram.h"
#include "ImGuiLayer.h"
#include "Events/Events.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Renderer/ElementBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "SDL.h"
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
    _window->createWindow(_name, 800, 800, 0);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    _imGuiLayer = new ImGuiLayer();
    pushOverlay(_imGuiLayer);

    float vertices[] = {
       -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
        0,1,2,
        0,1,3
    };

    _vao = VertexArray::create();

    _layout= new VertexLayout({ {ShaderDataType::Float3, "Position"}
                                ,{ShaderDataType::Float4, "Color"}
                             });
                 
    _vbo = VertexBuffer::create();
    _vbo->setData(vertices, sizeof(vertices));
    _vbo->setLayout(_layout);
    _vao->addVertexBuffer(_vbo);

    _ibo = ElementBuffer::create();
    _ibo->setData(indices, sizeof(indices));
    _vao->addElementBuffer(_ibo);

    _program.compileShaders("/home/parth/dev/opengl/Sandbox/res/shaders/simpleshader.vert",
                            "/home/parth/dev/opengl/Sandbox/res/shaders/simpleshader.frag");
    _program.linkShaders();
}

void Application::run()
{
    while(_running)
    {
        _window->processInput();
    
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _program.bind();
        _vao->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        for (auto *layer : _layers)
            layer->onUpdate();

        _imGuiLayer->imGuiBegin();

        for(auto *layer : _layers)
            layer->onImGuiRender();

        _imGuiLayer->imGuiEnd();

        _window->swapBuffers();
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
