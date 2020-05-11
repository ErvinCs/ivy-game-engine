#pragma once

#include "../Core/InputHandler.h"
#include <memory>


namespace Ivy 
{
	/*
	 *
	 */
	class WindowsInputHandler : public InputHandler
	{
	public:
		virtual bool isKeyDownImpl(unsigned int keycode) override;
		virtual bool isMouseButtonDownImpl(unsigned int button) override;
		virtual std::pair<float, float> getMousePositionImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};

}