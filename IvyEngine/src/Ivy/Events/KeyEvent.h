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
			IVY_CORE_INFO("Created: KeyEvent/KeyDownEvent: keyCode={0}, repeatCount={1}", keyCode, repeatCount);
		}

		inline int getRepeatCount() const {
			return repeatCount;
		}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyDownEvent: " << keyCode << "; Repeat count: " << repeatCount;
			return ss.str();
			//String str = String("KeyPressedEvent: " + keyCode) + String("; Repeat count: " + repeatCount);
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
			std::stringstream ss;
			ss << "KeyUpEvent: " << keyCode;
			return ss.str();
			//return String("KeyReleasedEvent: " + keyCode);
		}
	};

}