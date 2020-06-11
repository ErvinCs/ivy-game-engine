#pragma once
#include "../Context.h"
#include "../../Core/Logger.h"

struct GLFWwindow;

namespace Ivy 
{
	/**
	 * OpenGL render context.
	 * @see Context
	 */
	class OpenGLContext : public Context
	{
	public:
		/**
		 * Intializes the window handle.
		 * @param window GLFWwindow handle
		 */
		OpenGLContext(GLFWwindow* window);

		/**
		 * Loads the required GLAD function pointers and makes this context current.
		 */
		virtual void init() override;

		/**
		 * Swap buffers. Calls glfwSwapBuffers.
		 */
		virtual void refresh() override;
	private:
		GLFWwindow* window;
	};
}
