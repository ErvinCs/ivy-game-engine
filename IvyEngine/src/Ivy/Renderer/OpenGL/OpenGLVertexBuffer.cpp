#include "ivypch.h"
#include "OpenGLVertexBuffer.h"

#include "OpenGLRenderer.h"

namespace Ivy {

	OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, unsigned int size)
	{
		GLCall(glGenBuffers(1, &rendererId));	// &buffer - store in the return param the buffer address
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
		// Provide the buffer with the data
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &rendererId));
	}

	void OpenGLVertexBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
	}

	void OpenGLVertexBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

}