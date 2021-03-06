#include "ivypch.h"
#include "WindowsWindow.h"

#include "../Renderer/OpenGL/OpenGLContext.h"

namespace Ivy {

	static bool windowIsInitalized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		IVY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	std::unique_ptr<Window> Window::Create(const WindowProperties& properties)
	{
		return std::make_unique<WindowsWindow>(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) 
	{
		init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		IVY_CORE_INFO("WindowsWindow: Destroying WindowsWindow");
		shutdown();
	}

	void WindowsWindow::update()
	{
		glfwPollEvents();
		context->refresh();
	}

	void WindowsWindow::init(const WindowProperties& wProps)
	{
		IVY_CORE_INFO("WindowsWindow: Initializing");
		this->properties.wProps.name = wProps.name;
		this->properties.wProps.width = wProps.width;
		this->properties.wProps.height = wProps.height;


		if (!windowIsInitalized)
		{
			int init = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallback);
			windowIsInitalized = true;
		}

		// Create and init context & window
		this->window = glfwCreateWindow(wProps.width, wProps.height, wProps.name.c_str(), nullptr, nullptr);
		context = Context::Create(window);
		context->init();

		glfwSetWindowUserPointer(window, &properties);
		glfwSwapInterval(1);

		// Event Callbacks
		IVY_CORE_INFO("WindowsWindow: Initializing: Setting WindowResizeEvent Callback");
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
		
			data.wProps.width = width;
			data.wProps.height = height;
			WindowResizeEvent resizeEvent(width, height);
			resizeEvent.type = 2;
			data.callback(resizeEvent);
		});

		IVY_CORE_INFO("WindowsWindow: Initializing: Setting WindowCloseEvent Callback");
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent closeEvent;
			closeEvent.type = 1;
			data.callback(closeEvent);
		});

		IVY_CORE_INFO("WindowsWindow: Initializing: Setting Key Callbacks");
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyDownEvent keyEvent(key, 0);
					keyEvent.type = 3;
					data.callback(keyEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyUpEvent keyEvent(key);
					keyEvent.type = 4;
					data.callback(keyEvent);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyDownEvent keyEvent(key, 1);
					keyEvent.type = 5;
					data.callback(keyEvent);
					break;
				}
			}
		});

		IVY_CORE_INFO("WindowsWindow: Initializing: Setting Mouse Callback");
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonDownEvent mouseEvent(button);
					mouseEvent.type = 6;
					data.callback(mouseEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonUpEvent mouseEvent(button);
					mouseEvent.type = 7;
					data.callback(mouseEvent);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			
			MouseScrollEvent scrollEvent((float)xOffset, (float)yOffset);
			scrollEvent.type = 8;
			data.callback(scrollEvent);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) 
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			
			MouseMoveEvent moveEvent((float)xPos, (float)yPos);
			moveEvent.type = 9;
			data.callback(moveEvent);
		});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(window);
	}

}