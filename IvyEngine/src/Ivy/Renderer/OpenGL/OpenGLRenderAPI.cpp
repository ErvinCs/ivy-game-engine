#include "ivypch.h"
#include "OpenGLRenderAPI.h"

#include <iostream>


namespace Ivy {

	void OpenGLRenderAPI::init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderAPI::drawIndexed(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader)
	{
		// Bind shaders & uniforms - to the GPU to render the data
		shader.bind();
		// Bind the VAO - contains all the data
		va.bind();
		// Bind the Index Buffer - contains the indices into the vertex buffer
		ib.bind();

		// Issue a draw call using the index buffer - access the vertex buffer and call the shader for each vertex
		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void OpenGLRenderAPI::clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void OpenGLRenderAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

}