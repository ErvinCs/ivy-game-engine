#include "ivypch.h"
#include "OpenGLIndexBuffer.h"

#include "OpenGLRenderAPI.h"

namespace Ivy {
	
	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* data, uint32_t count)
	{
		this->count = count;

		// &buffer - store in the return param the buffer address
		GLCall(glGenBuffers(1, &rendererId));	
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
		// Provide the buffer with the data
		// Assume that sizeof(unsigned int) = sizeof(GLuint)
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));	
	}


	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &rendererId));
	}

	void OpenGLIndexBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererId));
	}

	void OpenGLIndexBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}