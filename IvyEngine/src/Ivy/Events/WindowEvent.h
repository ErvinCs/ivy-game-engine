#pragma once

#include "Event.h"


namespace Ivy {

	class WindowResizeEvent : public Event
	{
	private:
		unsigned int width, height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height) 
		{
			//IVY_CORE_INFO("Created: WindowEvent/WindowResizeEvent: width={0}, height={1}", width, height);
		}

		inline unsigned int getWidth() const { return width; }
		inline unsigned int getHeight() const { return height; }

		std::string toString() const override
		{
			//String str = String("WindowResizeEvent: " + width) + String("," + height);
			std::stringstream ss;
			ss << "WindowResizeEvent: width=" << width << ",height=" << height;
			return ss.str();
		}

	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() 
		{
			//IVY_CORE_INFO("Created: WindowEvent/WindowClosedEvent");
		}

		std::string toString() const override
		{
			//String str = String("WindowClosedEvent.");
			return "WindowClosedEvent";
		}
	};

}