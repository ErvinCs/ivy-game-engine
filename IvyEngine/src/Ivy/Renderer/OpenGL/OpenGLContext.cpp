#include "ivypch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
/////////////////////
#include <gl/GL.h>
////////////////////

namespace Ivy {
	OpenGLContext::OpenGLContext(GLFWwindow* window) : window(window)
	{
		IVY_CORE_TRACE("Window status: {0}", window != nullptr);
	}


	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		IVY_CORE_TRACE("Glad status: {0}", status);
	}

	void OpenGLContext::refresh()
	{
		glfwSwapBuffers(window);
	}
}