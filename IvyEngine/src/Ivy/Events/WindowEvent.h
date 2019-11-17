#pragma once

#include "Event.h"


namespace Ivy {

	class WindowResizeEvent : public Event
	{
	private:
		unsigned int width, height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height) {}

		inline unsigned int getWidth() const { return width; }
		inline unsigned int getHeight() const { return height; }

		String toString() const
		{
			String str = String("WindowResizeEvent: " + width) + String("," + height);
			return str;
		}

	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		String toString() const
		{
			String str = String("WindowClosedEvent.");
			return str;
		}
	};

}