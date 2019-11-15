#include "ivypch.h"
#include "OpenGLIndexBuffer.h"

#include "OpenGLRenderer.h"

namespace Ivy {
	
	OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count)
	{
		this->count = count;
		ASSERT(sizeof(unsigned int) == sizeof(GLuint));

		GLCall(glGenBuffers(1, &rendererId));	// &buffer - store in the return param the buffer address
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
		// Provide the buffer with the data
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));	// Assume that sizeof(unsigned int) = sizeof(GLuint)
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