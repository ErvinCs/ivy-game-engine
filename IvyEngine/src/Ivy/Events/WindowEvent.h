#pragma once

#include "Event.h"


namespace Ivy {
	/**
	 * Event raise din response to resizing an application window,
	 * @see Event
	 * @see Window
	 */
	class WindowResizeEvent : public Event
	{
	private:
		// The size of the window in screen coordinates
		unsigned int width, height;
	public:
		/**
		 * Constructs a WindowResizeEvent
		 * @param width the width of the window in screen coordinates
		 * @param height the height of the window in screen coordinates
		 */
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height) {}

		// @returns int the width of the window in screen coordinates
		inline unsigned int getWidth() const { return width; }

		// @returns int the height of the window in screen coordinates
		inline unsigned int getHeight() const { return height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: width=" << width << ",height=" << height;
			return ss.str();
		}
	};

	/**
	 * Event raised in response to closing an application Window
	 * @see Event
	 * @see Window
	 */
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		std::string toString() const override
		{
			return "WindowClosedEvent";
		}
	};
}