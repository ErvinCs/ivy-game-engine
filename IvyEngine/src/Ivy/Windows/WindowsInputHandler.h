#pragma once

#include "../Core/InputHandler.h"
#include <memory>
#include <GLFW/glfw3.h>

namespace Ivy {

	class WindowsInputHandler : public InputHandler
	{
	public:
		//std::unique_ptr<InputHandler> InputHandler::instance = std::unique_ptr<WindowsInputHandler>();

		virtual bool IsKeyPressedImpl(unsigned int keycode) override;
		virtual bool IsMouseButtonPressedImpl(unsigned int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}