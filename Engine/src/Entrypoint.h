#include "Application.h"
#include "Engine.h"
#include "Log.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    Engine::Log::init();
    Engine::Application* app = Engine::CreateApplication();
    app->run();
    delete app;
}
