#include <iostream>

#include "ExampleLayer.h"
#include "MainGame.h"

MainGame::MainGame(const std::string &name)
    :Application(name)
{
    pushLayer(new ExampleLayer("ExampleLayer"));
}

MainGame::~MainGame()
{
}

Engine::Application* Engine::CreateApplication()
{
    return new MainGame("Game");
}

