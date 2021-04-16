#pragma once

namespace Engine{

class Application{
public:
    Application();
    virtual ~Application();

    virtual void run();
private:
};

Application* CreateApplication();

}


