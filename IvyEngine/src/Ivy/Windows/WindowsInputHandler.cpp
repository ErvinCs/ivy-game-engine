#include "ivypch.h"
#include "WindowsInputHandler.h"

#include "../Core/Application.h"

#include <GLFW/glfw3.h>

namespace Ivy {
	std::unique_ptr<InputHandler> InputHandler::instance = std::make_unique<WindowsInputHandler>();
	//InputHandler* InputHandler::instance = new WindowsInputHandler();

	bool WindowsInputHandler::IsKeyDownImpl(unsigned int keycode)
	{
		// Get the glfw window reference
		auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInputHandler::IsMouseButtonDownImpl(unsigned int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInputHandler::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::getApplication().getWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInputHandler::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInputHandler::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

}