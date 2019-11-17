#include "ivypch.h"
#include "WindowsInputHandler.h"

namespace Ivy {


	bool WindowsInputHandler::IsKeyPressedImpl(unsigned int keycode)
	{
		return false;
	}

	bool WindowsInputHandler::IsMouseButtonPressedImpl(unsigned int button)
	{
		return false;
	}

	std::pair<float, float> WindowsInputHandler::GetMousePositionImpl()
	{
		return { 0.0f, 0.0f };
	}

	float WindowsInputHandler::GetMouseXImpl()
	{
		return 0.0f;
	}

	float WindowsInputHandler::GetMouseYImpl()
	{
		return 0.0f;
	}

}