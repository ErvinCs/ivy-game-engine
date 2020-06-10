#pragma once

#include "Event.h"


namespace Ivy {
	/*
	 *
	 */
	class KeyEvent : public Event
	{
	public:

		/**
		 *
		 */
		inline int getKeyCode() const {
			return keyCode;
		}
	protected:

		/**
		 *
		 */
		KeyEvent(int keyCode)
		{
			this->keyCode = keyCode;
		}

		//
		int keyCode;
	};

	/*
	 *
	 */
	class KeyDownEvent : public KeyEvent
	{
	public:
		
		/**
		 *
		 */
		KeyDownEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}

		/**
		 *
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

	/*
	 *
	 */
	class KeyUpEvent : public KeyEvent
	{
	public:
		/**
		 *
		 */
		KeyUpEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyUpEvent: " << keyCode;
			return ss.str();
		}
	};

}