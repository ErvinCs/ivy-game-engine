#pragma once

#include "../Core/InputHandler.h"
#include <memory>


namespace Ivy 
{
	/**
	 * Implementation of the InputHandler for Windows.
	 * @see: InputHandler
	 */
	class WindowsInputHandler : public InputHandler
	{
	public:

		/**
		 * Check if the keyboard key with the passed `keycode` is down.
		 * @param keycode unsigned int represents the code of the key
		 * @returns true if the key is down and false otherwise
		 */
		virtual bool isKeyDownImpl(unsigned int keycode) override;

		/**
		 * Check if the mouse button with the passed `button` is down.
		 * @param button unsigned int represents the code of the button
		 * @returns true if the button is down and false otherwise
		 */
		virtual bool isMouseButtonDownImpl(unsigned int button) override;

		/**
		 * @returns pair<float,float> as the position of the mouse
		 */
		virtual std::pair<float, float> getMousePositionImpl() override;

		/**
		 * @returns float the position of the mouse on the X axis
		 */
		virtual float getMouseXImpl() override;

		/**
		 * @returns float the position of the mouse on the Y axis
		 */
		virtual float getMouseYImpl() override;
	};

}