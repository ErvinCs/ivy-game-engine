#pragma once

#include "Event.h"


namespace Ivy {
	/**
	 * Base class for all `Event`s related to key events.
	 * @see Event
	 */
	class KeyEvent : public Event
	{
	public:

		/**
		 * @returns int the key code associated to the key that triggers this Event
		 */
		inline int getKeyCode() const {
			return keyCode;
		}
	protected:

		/**
		 * Constructs a base KeyEvent
		 * @param keyCode the key code associated to the key that triggers this Event
		 */
		KeyEvent(int keyCode)
		{
			this->keyCode = keyCode;
		}

		// The key code associated to the key that triggers this Event
		int keyCode;
	};

	/**
	 * Event raised in response to pressing down a key.
	 * Takes into account "long" key presses, having a delay between the 1st press and subsequent registered presses
	 * @see KeyEvent
	 */
	class KeyDownEvent : public KeyEvent
	{
	public:
		
		/**
		 * Constructs a KeyDownEvent.
		 * @param keyCode int the key code associated to the key that triggers this Event
		 * @param repeatCount 0 if a single press is registered, 1 if multiple
		 */
		KeyDownEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}

		/**
		 * @returns int the repeat count
		 */
		inline int getRepeatCount() const {
			return repeatCount;
		}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyDownEvent: " << keyCode << "; Repeat count: " << repeatCount;
			return ss.str();
		}

	private:
		int repeatCount;
	};

	/**
	 * Event raised in response to releasing a key.
	 * @see KeyEvent
	 */
	class KeyUpEvent : public KeyEvent
	{
	public:
		/**
		 * @param keyCode the key code associated to the key that triggers this Event
		 */
		KeyUpEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyUpEvent: " << keyCode;
			return ss.str();
		}
	};

}