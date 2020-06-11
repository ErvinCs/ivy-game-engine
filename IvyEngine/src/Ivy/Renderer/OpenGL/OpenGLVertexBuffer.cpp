#include "ivypch.h"
#include "OpenGLVertexBuffer.h"

#include "OpenGLRenderAPI.h"

namespace Ivy {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
	{
		// &buffer - store in the return param the buffer address
		GLCall(glGenBuffers(1, &rendererId));	
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
		// Provide the buffer with the data
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		GLCall(glGenBuffers(1, &rendererId));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	void OpenGLVertexBuffer::setData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
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