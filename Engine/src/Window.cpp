#include "Window.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_stdinc.h"
#include "SDL_video.h"
#include "glad/glad.h"
#include "Log.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "Events/Events.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/ApplicationEvent.hpp"
#include <functional>

namespace Engine{

Window::Window()
    :_data({0, 0})
    ,_window(nullptr)
{
}

Window::~Window()
{
}

int Window::event_filter(void* data, SDL_Event* e)
{
    auto window = static_cast<Window*>(data);
    switch (e->type)
    {
        case SDL_QUIT:{
              WindowCloseEvent close_ev;
              window->_data._callback(close_ev);
              break;
              }

        case SDL_MOUSEBUTTONDOWN:{
              MouseButtonPressedEvent pressed_ev(static_cast<MouseCode>(e->button.button));
              window->_data._callback(pressed_ev);
              break;
              }

        case SDL_MOUSEBUTTONUP:{
              MouseButtonReleasedEvent released_ev(static_cast<MouseCode>(e->button.button));
              window->_data._callback(released_ev);
              break;
              }

        case SDL_KEYDOWN:{
              KeyPressedEvent keypressed_ev(static_cast<KeyCode>(e->key.keysym.sym),e->key.repeat);
              window->_data._callback(keypressed_ev); 
              break;
              }

        case SDL_WINDOWEVENT:{
              switch (e->window.event){
                  case SDL_WINDOWEVENT_RESIZED:
                      WindowResizeEvent resize_ev(e->window.data1, e->window.data2);
                      window->_data._callback(resize_ev);
                      break;
              }
              }
    }

    return 1;
}

int Window::createWindow(std::string const &name, int width, int height, unsigned int curr_flags)
{
    _data._width = width;
    _data._height = height;

    Uint32 flags = SDL_WINDOW_OPENGL;
    
    if (curr_flags & INVISIBLE)
        flags |= SDL_WINDOW_HIDDEN;
    if (curr_flags & FULLSCREEN)
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (curr_flags & BORDERLESS)
        flags |= SDL_WINDOW_BORDERLESS;

    _window = SDL_CreateWindow("Game",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width,
                               height,
                               flags);

    SDL_SetWindowResizable(_window, SDL_TRUE);

    if (!_window) {
        ERROR("SDL failed to create a window");
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);

    if (!glContext) {
        ERROR("GLContext could not be created");
        return -1;
    }
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        ERROR("Glad was unable to load");
        return -1;
    }


    INFO("OpenGL version: {}", glGetString(GL_VERSION));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //set VSYNC
    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(_window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    SDL_AddEventWatch(event_filter, this);

    return 1;
}

void Window::swapBuffers()
{
    SDL_GL_SwapWindow(_window);
}

}
