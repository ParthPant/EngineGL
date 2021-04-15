#pragma once

#include "glm/glm.hpp"
#include <unordered_map>
namespace Engine{

class InputManager{
public:
    InputManager();
    ~InputManager();

    void pressKey(unsigned int const key_id);
    void releaseKey(unsigned int const key_id);

    bool isKeyPressed(unsigned int const key_id);

    void setMouseCoords(float x, float y);
    glm::vec2 getMouseCoords() const {return _mousecoords;};

private:
    std::unordered_map<unsigned int, bool> _keymap;
    glm::vec2 _mousecoords;
};

}
