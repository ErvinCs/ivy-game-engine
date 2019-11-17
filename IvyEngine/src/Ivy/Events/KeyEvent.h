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

	class KeyPressedEvent : public KeyEvent
	{
	public:
		
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}

		inline int getRepeatCount() const {
			return repeatCount;
		}

		String toString() const {
			String str = String("KeyPressedEvent: " + keyCode) + String("; Repeat count: " + repeatCount);
			return str;
		}

	private:
		int repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

		String toString() const {
			return String("KeyReleasedEvent: " + keyCode);
		}
	};

}