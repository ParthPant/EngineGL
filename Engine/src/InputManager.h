#pragma once

#include "glm/glm.hpp"

namespace Engine{

class InputManager{
public:
    ~InputManager();

    static bool isKeyPressed(unsigned int const key_id);
    static uint8_t getMouseState();
    static glm::vec2 getMouseCoords(); 
private:
    InputManager();
};

}
