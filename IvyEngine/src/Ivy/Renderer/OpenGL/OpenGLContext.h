#pragma once
#include "../Context.h"
#include "../../Core/Logger.h"

struct GLFWwindow;

namespace Ivy {

	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* window);
		~OpenGLContext() = default;

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* window;
	};
}
