#include "InputManager.h"

namespace Engine{

InputManager::InputManager()
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

}
