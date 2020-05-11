#pragma once
#include "../Context.h"
#include "../../Core/Logger.h"

struct GLFWwindow;

namespace Ivy 
{
	/*
	 *
	 */
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void init() override;
		virtual void refresh() override;
	private:
		GLFWwindow* window;
	};
}
