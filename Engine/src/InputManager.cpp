#include "InputManager.h"

namespace Engine{

InputManager::InputManager()
    :_mousecoords(0.0f)
{
}

InputManager::~InputManager()
{
}

void InputManager::pressKey(unsigned int const key_id)
{
    _keymap[key_id] = true;
}

void InputManager::releaseKey(unsigned int const key_id)
{
    _keymap[key_id] = false;
}

bool InputManager::isKeyPressed(unsigned int const key_id)
{
    auto it = _keymap.find(key_id);

    if (it != _keymap.end())
        return _keymap[key_id];

    return false;
}

void InputManager::setMouseCoords(float x, float y)
{
    _mousecoords.x = x;
    _mousecoords.y = y;
}

}
