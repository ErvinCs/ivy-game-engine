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
		//IVY_CORE_TRACE("WindowsInputHandler: isKeyDownImpl: keycode={0}", keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInputHandler::isMouseButtonDownImpl(unsigned int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		//IVY_CORE_TRACE("WindowsInputHandler: isMouseButtonDownImpl: button={0}", button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInputHandler::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetApplication().getWindow().getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		//IVY_CORE_TRACE("WindowsInputHandler: getMousePositionImpl: position=({0},{1})", xpos, ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInputHandler::getMouseXImpl()
	{
		auto[x, y] = getMousePositionImpl();
		//IVY_CORE_TRACE("WindowsInputHandler: getMouseXImpl: mouseX={0})", x);
		return x;
	}

	float WindowsInputHandler::getMouseYImpl()
	{
		auto[x, y] = getMousePositionImpl();
		//IVY_CORE_TRACE("WindowsInputHandler: getMouseXImpl: mouseY={0})", y);
		return y;
	}

}