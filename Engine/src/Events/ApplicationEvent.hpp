#pragma once

#include <string>
#include <sstream>
#include "Events.hpp"

namespace Engine{

class WindowCloseEvent : public Event{
public:
   WindowCloseEvent() 
   {
   }

   EVENT_CLASS_TYPE(WindowClose)
   EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
};

class WindowResizeEvent : public Event
	{
	private:
		unsigned int _width, _height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: _width(width), _height(height) {}

		unsigned int getWidth() const { return _width; }
		unsigned int getHeight() const { return _height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << _width << ", " << _height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}
