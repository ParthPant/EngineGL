#include "Application.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Engine::CreateApplication();
    app->run();
    delete app;
}
