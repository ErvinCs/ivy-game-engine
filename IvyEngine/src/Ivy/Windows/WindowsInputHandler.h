#pragma once

#include "../Core/InputHandler.h"
#include <memory>


namespace Ivy {

	class WindowsInputHandler : public InputHandler
	{
	public:
		//std::unique_ptr<InputHandler> InputHandler::instance = std::unique_ptr<WindowsInputHandler>();

		virtual bool IsKeyDownImpl(unsigned int keycode) override;
		virtual bool IsMouseButtonDownImpl(unsigned int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}