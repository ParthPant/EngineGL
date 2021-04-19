#pragma once

#include "Events.hpp"
#include "SDL2/SDL_mouse.h"

#include <sstream>

namespace Engine{

enum MouseCode{
    MOUSE_BUTTON_LEFT   = 1,
    MOUSE_BUTTON_MIDDLE = 2,
    MOUSE_BUTTON_RIGHT  = 3
};

class MouseMovedEvent : public Event { 
public: 
    MouseMovedEvent(const float x, const float y) : _MouseX(x), _MouseY(y) {}

    float GetX() const { return _MouseX; }
    float GetY() const { return _MouseY; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << _MouseX << ", " << _MouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
    float _MouseX, _MouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(const float xOffset, const float yOffset)
        : _XOffset(xOffset), _YOffset(yOffset) {}

    float GetXOffset() const { return _XOffset; }
    float GetYOffset() const { return _YOffset; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
    float _XOffset, _YOffset;
};

class MouseButtonEvent : public Event
{
public:
    MouseCode GetMouseButton() const { return _button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
protected:
    MouseButtonEvent(const MouseCode button)
        : _button(button) {}

    MouseCode _button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(const MouseCode button)
        : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << _button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(const MouseCode button)
        : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << _button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

}
