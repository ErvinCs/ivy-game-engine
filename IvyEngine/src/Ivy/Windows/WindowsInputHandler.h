#pragma once

#include "../Core/InputHandler.h"

namespace Ivy {

	class WindowsInputHandler : public InputHandler
	{
	public:
		virtual bool IsKeyPressedImpl(unsigned int keycode) override;

		virtual bool IsMouseButtonPressedImpl(unsigned int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}