#include "ivypch.h"
#include "OpenGLRenderer.h"

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

	void OpenGLRenderer::draw(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader) const
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

	void OpenGLRenderer::clear() const
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

}