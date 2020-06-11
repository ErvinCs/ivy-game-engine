#pragma once

#include "Event.h"


namespace Ivy {
	/**
	 * Event raised in response to moving the cursor.
	 * @see Event
	 */
	class MouseMoveEvent : public Event
	{
	private:
		// Capture the cursor position in screen coordinates
		float x, y;
	public:
		/**
		 * Constructs a base MouseEvent
		 * @param x position of the cursor on the X-Axis
		 * @param y position of the cursor on the Y-Axis
		 */
		MouseMoveEvent(float x, float y)
			: x(x), y(y) {}

		// @returns x position of the cursor on the X-Axis
		inline float getX() const { return x; }

		// @returns y position of the cursor on the Y-Axis
		inline float getY() const { return y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: x=" << x << ",y=" << y;
			return ss.str();
		}
	};

	/**
	 * Event raised in response to scrolling.
	 * @see Event
	 */
	class MouseScrollEvent : public Event
	{
	private:
		// Capture the cursor position in screen coordinates
		float x, y;
	public:
		MouseScrollEvent(float x, float y)
			: x(x), y(y) {}

		// @returns the position of the cursor on the X-Axis relative to the position it was previous to the Event
		inline float getXOffset() const { return x; }
		// @returns the position of the cursor on the Y-Axis relative to the position it was previous to the Event
		inline float getYOffset() const { return y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: x=" << x << ",y=" << y;
			return ss.str();
		}

	};

	/**
	 * Base class for Events raised in response to pressing a mouse button.
	 * @see Event
	 */
	class MouseButtonEvent : public Event
	{
	public:
		// @returns int the button code of the pressed mouse button
		inline int getMouseButton() const { return button; }

	protected:
		MouseButtonEvent(int button)
			: button(button) {}

		// The button code of the pressed mouse button
		int button;
	};

	/**
	 * Event raised in response to pressing down a mouse button.
	 * @see MouseEvent
	 */
	class MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		/**
		 * Constructs a MouseButtonDownEvent
		 * @param button the code of the pressed mouse button
		 */
		MouseButtonDownEvent(int button)
			: MouseButtonEvent(button) 
		{}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDownEvent: button=" << button;
			return ss.str();
		}
	};

	/**
	 * Event raised in response to releasing a mouse button
	 * @see MouseEvent
	 */
	class MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		/**
		 * Constructs a MouseButtonDownEvent
		 * @parma button the code of the released mouse button
		 */
		MouseButtonUpEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUpEvent: button=" << button;
			return ss.str();
		}
	};

}