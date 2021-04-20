#pragma once

#include <functional>
#include <string>

#define BIT(x) (1 << x)

namespace Engine{

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

enum class EventType{
    NONE = 0,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    WindowClose, WindowResize
};

enum EventCategory
{
    NONE = 0,
    EventCategoryApplication  = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4),
};

class Event{
public:
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getCategoryFlags() const = 0;
    virtual std::string toString() const {return getName();}

    bool isHandled() {return _handled;}
    void setHandled(bool h) {_handled = h;}

    inline bool isInCategory(EventCategory c)
    {
        return getCategoryFlags() & c;
    }
protected:
    bool _handled = false;
    friend class EventDispatcher;
};

class EventDispatcher{
public:
    EventDispatcher(Event &e)
	:_event(e)
    {
    }

    template<typename T, typename F>
    bool dispatch(const F& func)
    {
	if (_event.getEventType() == T::getStaticType())
	{
	    _event._handled |= func(static_cast<T&>(_event));
	    return true;
	}
	return false;
    }

private:
    Event& _event;
};

}
