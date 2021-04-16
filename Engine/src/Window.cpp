#include "Window.h"
#include "SDL.h"
#include "SDL_video.h"
#include "glad/glad.h"
#include "Log.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace Engine{

Window::Window()
    :_width(0)
    ,_height(0)
    ,_window(nullptr)
{
}

Window::~Window()
{
}

int Window::createWindow(std::string const &name, int width, int height, unsigned int curr_flags)
{
    _width = width;
    _height = height;

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

    return 1;
}

void Window::swapBuffers()
{
    SDL_GL_SwapWindow(_window);
}

}
