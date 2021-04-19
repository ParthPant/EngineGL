#pragma once

#include "Events.hpp"
#include "SDL2/SDL_keycode.h"

#include <sstream>

namespace Engine{

typedef SDL_KeyCode KeyCode;

class KeyEvent : public Event
{
public:
    KeyCode getKeyCode() const { return _KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
    KeyEvent(const KeyCode keycode)
        : _KeyCode(keycode) {}

    KeyCode _KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
        : KeyEvent(keycode), _RepeatCount(repeatCount) {}

    uint16_t getRepeatCount() const { return _RepeatCount; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << _KeyCode << " (" << _RepeatCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
private:
    uint16_t _RepeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(const KeyCode keycode)
        : KeyEvent(keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << _KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
public:
    KeyTypedEvent(const KeyCode keycode)
        : KeyEvent(keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << _KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};

}
