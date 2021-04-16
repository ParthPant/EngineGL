#pragma once

#include <SDL2/SDL_video.h>
#include <string>

namespace Engine{

enum WindowFlags{
    INVISIBLE = 0x1,
    FULLSCREEN = 0x2,
    BORDERLESS = 0x4
};

class Window{
public:
    Window();
    ~Window();

    int createWindow(std::string const &name, int width, int height, unsigned int flags);

    int getScreenWidth() { return _width; }
    int getScreenHeight() { return _height;}

    SDL_Window *getWindow(){ return _window; }

    void swapBuffers();
private:
    SDL_Window *_window;
    int _width;
    int _height;
};

}
