#pragma once

#include <SDL2/SDL_video.h>
#include <SDL_events.h>
#include <string>
#include <functional>
#include <Events/Events.hpp>

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

    using EventCallbackFn = std::function<void(Event &ev)>;

    int createWindow(std::string const &name, int width, int height, unsigned int flags);

    int getScreenWidth() { return _data._width; }
    int getScreenHeight() { return _data._height;}

    SDL_Window *getWindow(){ return _window; }

    void swapBuffers();

    void setEventCallback(const EventCallbackFn& callback){_data._callback = callback;};
    static int event_filter(void* data, SDL_Event* e);
private:
    SDL_Window *_window;
    int windowEvents();


    struct WindowData {
        int _width;
        int _height;
        EventCallbackFn _callback;
    } _data;
};

}
