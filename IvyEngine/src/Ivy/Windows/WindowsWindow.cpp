#include "ivypch.h"
#include "WindowsWindow.h"

#include "../Renderer/OpenGL/OpenGLContext.h"

namespace Ivy {

	static bool windowIsInitalized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		IVY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties) 
	{
		init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::update()
	{
		glfwPollEvents();
		context->swapBuffers();

	}

	void WindowsWindow::init(const WindowProperties& wProps)
	{
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
		context = new OpenGLContext(window);
		context->init();

		glfwSetWindowUserPointer(window, &properties);
		glfwSwapInterval(1);

		// Event Callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
		
			data.wProps.width = width;
			data.wProps.height = height;
			WindowResizeEvent resizeEvent(width, height);
			data.callback(resizeEvent);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent closeEvent;
			data.callback(closeEvent);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyDownEvent keyEvent(key, 0);
					data.callback(keyEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyUpEvent keyEvent(key);
					data.callback(keyEvent);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyDownEvent keyEvent(key, 1);
					data.callback(keyEvent);
					break;
				}
			}
		});

		/*glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int char* character)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent typedEvent(character);
			data.callback(typedEvent);
		});*/

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonDownEvent mouseEvent(button);
					data.callback(mouseEvent);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonUpEvent mouseEvent(button);
					data.callback(mouseEvent);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			
			MouseScrollEvent scrollEvent((float)xOffset, (float)yOffset);
			data.callback(scrollEvent);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) 
		{
			WindowPropertiesUserData& data = *(WindowPropertiesUserData*)glfwGetWindowUserPointer(window);
			
			MouseMoveEvent moveEvent((float)xPos, (float)yPos);
			data.callback(moveEvent);
		});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(window);
	}

}