#include "ivypch.h"
#include "OpenGLRenderAPI.h"

#include <iostream>

void GLClearError()
{
	// Get the errors until all the flags are cleared
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	// While errors are actually retrieved
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error]: " << error
			<< "; function: " << function
			<< "; file: " << file
			<< "; line: " << line
			<< std::endl;
		return false;
	}
	return true;
}

namespace Ivy {

	void OpenGLRenderAPI::init()
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_TEXTURE_2D));
	}
	void OpenGLRenderAPI::draw(const std::shared_ptr<VertexArray>& va)
	{
		GLCall(glDrawElements(GL_TRIANGLES, va->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void OpenGLRenderAPI::clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGLRenderAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		GLCall(glViewport(x, y, width, height));
	}

	void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
	{
		GLCall(glClearColor(color.r, color.g, color.b, color.a));
	}
}