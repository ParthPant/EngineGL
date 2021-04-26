#include "InputManager.h"
#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "fwd.hpp"

namespace Engine{

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

uint8_t InputManager::getMouseState()
{
    if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
        return 1;
    if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2))
        return 2;
    if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3))
        return 3;
    else return 0;
}

bool InputManager::isKeyPressed(unsigned int const key_id)
{
    uint8_t const *state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(key_id)];
}

glm::vec2 InputManager::getMouseCoords()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return glm::vec2(x, y);
}

}
