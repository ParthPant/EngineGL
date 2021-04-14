#pragma once

#include <unordered_map>
namespace Engine{

class InputManager{
public:
    InputManager();
    ~InputManager();

    void pressKey(unsigned int const key_id);
    void releaseKey(unsigned int const key_id);

    bool isKeyPressed(unsigned int const key_id);

private:
    std::unordered_map<unsigned int, bool> _keymap;
};

}
