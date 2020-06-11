#pragma once

#include "Logger.h"

namespace Ivy{
	/**
	 * Provides static methods to query the state of input devices.
	 * Supports keyboard and mouse devices.
	 * Children are required to implement the methods: 
	 *	isKeyDownImpl, isMouseButtonDownImpl, getMousePositionImpl, getMouseXImpl, getMouseYImpl
	 */
	class InputHandler
	{
	public:
		~InputHandler() = default;

		/**
		 * Check if the keyboard key with the passed `keycode` is down.
		 * @param keycode unsigned int represents the code of the key
		 * @returns true if the key is down and false otherwise
		 */
		inline static bool IsKeyDown(unsigned int keycode) 
		{
			return instance->isKeyDownImpl(keycode);
		}
		
		/**
		 * Check if the mouse button with the passed `button` is down.
		 * @param button unsigned int represents the code of the button
		 * @returns true if the button is down and false otherwise
		 */
		inline static bool IsMouseButtonDown(unsigned int button) 
		{
			return instance->isMouseButtonDownImpl(button);
		}
		
		/**
		 * @returns pair<float,float> as the position of the mouse
		 */
		inline static std::pair<float, float> GetMousePosition() 
		{ 
			return instance->getMousePositionImpl(); 
		}
		
		/**
		 * @returns float the position of the mouse on the X axis
		 */
		inline static float GetMouseX() 
		{ 
			return instance->getMouseXImpl(); 
		}
		
		/**
		 * @returns float the position of the mouse on the Y axis
		 */
		inline static float GetMouseY() 
		{ 
			return instance->getMouseYImpl(); 
		}

		/**
		 * @returns the singular InputHandler instance
		 */
		inline static std::unique_ptr<InputHandler>& GetInstance() { return instance; }

	protected:
		InputHandler() = default;
		InputHandler(const InputHandler&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;

		// Implemented per platform. Calls the static IsKeyDown method. 
		virtual bool isKeyDownImpl(unsigned int keycode) = 0;
		// Implemented per platform. Calls the static IsMouseButtonDown method. 
		virtual bool isMouseButtonDownImpl(unsigned int button) = 0;
		//Implemented per platform. Calls the static GetMousePosition method. 
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		// Implemented per platform. Calls the static GetMouseX method. 
		virtual float getMouseXImpl() = 0;
		// Implemented per platform. Calls the static GetMouseY method. 
		virtual float getMouseYImpl() = 0;

	private:
		// Singular InputHandler instance. Points to the InputHandler instantiated per platform.
		static std::unique_ptr<InputHandler> instance;
		
	};

}