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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void OpenGLRenderAPI::drawIndexed(const std::shared_ptr<VertexArray>& va)
	{
		GLCall(glDrawElements(GL_TRIANGLES, va->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr));
	}
	/*void OpenGLRenderAPI::drawIndexed(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader)
	{
		// Bind shaders & uniforms - to the GPU to render the data
		shader.bind();
		// Bind the VAO - contains all the data
		va.bind();
		// Bind the Index Buffer - contains the indices into the vertex buffer
		ib.bind();

		// Issue a draw call using the index buffer - access the vertex buffer and call the shader for each vertex
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}*/

	void OpenGLRenderAPI::clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void OpenGLRenderAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
}