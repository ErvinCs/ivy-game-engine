#pragma once

#include "Event.h"


namespace Ivy {

	class MouseMoveEvent : public Event
	{
	private:
		float x, y;
	public:
		MouseMoveEvent(float x, float y)
			: x(x), y(y) 
		{
			//IVY_CORE_INFO("Created: MouseEvent/MouseMoveEvent: x={0},y={1}", x, y);
		}

		inline float getX() const { return x; }
		inline float getY() const { return y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: x=" << x << ",y=" << y;
			return ss.str();

			//int X = x, Y = y;
			//String str = String("MouseMoveEvent: " + X) + String("," + Y);
		}
	};

	class MouseScrollEvent : public Event
	{
	private:
		float x, y;
	public:
		MouseScrollEvent(float x, float y)
			: x(x), y(y) 
		{
			//IVY_CORE_INFO("Created: MouseEvent/MouseScrollEvent: x={0},y={1}", x, y);
		}

		inline float getXOffset() const { return x; }
		inline float getYOffset() const { return y; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: x=" << x << ",y=" << y;
			return ss.str();

			//int X = x, Y = y;
			//String str = String("MouseScrollEvent: " + X) + String("," + Y);
		}

	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int getMouseButton() const { return button; }

	protected:
		MouseButtonEvent(int button)
			: button(button) 
		{
			//IVY_CORE_INFO("Created: MouseEvent/MouseButtonEvent: button={0}", button);
		}

		int button;
	};

	class MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		MouseButtonDownEvent(int button)
			: MouseButtonEvent(button) 
		{
			//IVY_CORE_INFO("Created: MouseEvent/MouseButtonDownEvent: button={0}", button);
		}

		std::string toString() const override
		{
			//String str = String("MouseButtonDownEvent: " + button);
			std::stringstream ss;
			ss << "MouseButtonDownEvent: button=" << button;
			return ss.str();
		}
	};

	class MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		MouseButtonUpEvent(int button)
			: MouseButtonEvent(button) 
		{
			//IVY_CORE_INFO("Created: MouseEvent/MouseButtonUpEvent: button={0}", button);
		}

		std::string toString() const override
		{
			//String str = String("MouseButtonUpEvent: " + button);
			std::stringstream ss;
			ss << "MouseButtonUpEvent: button=" << button;
			return ss.str();
		}
	};

}