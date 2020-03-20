#include "ivypch.h"
#include "WindowsInputHandler.h"

#include "../Core/Application.h"
#include "../Core/Logger.h"
#include <GLFW/glfw3.h>

namespace Ivy {
	std::unique_ptr<InputHandler> InputHandler::instance = std::make_unique<WindowsInputHandler>();

	bool WindowsInputHandler::isKeyDownImpl(unsigned int keycode)
	{
		// Get the glfw window reference
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		//WORKING PROPERLY
		//IVY_CORE_TRACE("WindowsInputHandler::IsKeyDownImpl. keycode={0}, press={1}, repeat={2}", keycode, state == GLFW_PRESS, state == GLFW_REPEAT);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInputHandler::isMouseButtonDownImpl(unsigned int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInputHandler::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().getWindow().getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInputHandler::getMouseXImpl()
	{
		auto[x, y] = getMousePositionImpl();
		return x;
	}

	float WindowsInputHandler::getMouseYImpl()
	{
		auto[x, y] = getMousePositionImpl();
		return y;
	}

}