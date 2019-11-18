#pragma once

#include "Event.h"


namespace Ivy {

	class KeyEvent : public Event
	{
	// TODO: getEventType / getEventName
	public:
		inline int getKeyCode() const {
			return keyCode;
		}
	protected:
		KeyEvent(int keyCode)
		{
			this->keyCode = keyCode;
		}

		int keyCode;
	};

	class KeyDownEvent : public KeyEvent
	{
	public:
		
		KeyDownEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) 
		{
			//IVY_CORE_INFO("Created: KeyEvent/KeyDownEvent: keyCode={0}, repeatCount={1}", keyCode, repeatCount);
		}

		inline int getRepeatCount() const {
			return repeatCount;
		}

		std::string toString() const override {
			//String str = String("KeyPressedEvent: " + keyCode) + String("; Repeat count: " + repeatCount);
			std::string str = "KeyPressedEvent: " + keyCode;
			return str;
		}

	private:
		int repeatCount;
	};

	class KeyUpEvent : public KeyEvent
	{
	public:
		KeyUpEvent(int keyCode) : KeyEvent(keyCode) 
		{
			IVY_CORE_INFO("Created: KeyEvent/KeyUpEvent: keyCode={0}", keyCode);
		}

		std::string toString() const override {
			return "KeyReleasedEvent: " + keyCode;
			//return String("KeyReleasedEvent: " + keyCode);
		}
	};

}