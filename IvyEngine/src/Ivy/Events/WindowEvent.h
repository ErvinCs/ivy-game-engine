#pragma once

#include "Event.h"


namespace Ivy {
	/**
	 *
	 */
	class WindowResizeEvent : public Event
	{
	private:
		//
		unsigned int width, height;
	public:
		/**
		 *
		 */
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height) {}

		//
		inline unsigned int getWidth() const { return width; }

		//
		inline unsigned int getHeight() const { return height; }

		//
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: width=" << width << ",height=" << height;
			return ss.str();
		}

	};

	/**
	 *
	 */
	class WindowCloseEvent : public Event
	{
	public:
		//
		WindowCloseEvent() {}

		//
		std::string toString() const override
		{
			return "WindowClosedEvent";
		}
	};

}