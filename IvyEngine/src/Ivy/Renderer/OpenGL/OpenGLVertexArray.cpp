#include "ivypch.h"
#include "OpenGLVertexArray.h"

#include "OpenGLVertexBufferLayout.h"

namespace Ivy {

	OpenGLVertexArray::OpenGLVertexArray()
	{
		GLCall(glGenVertexArrays(1, &rendererId));
	}


	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &rendererId));
	}

	void OpenGLVertexArray::addBuffer(const OpenGLVertexBuffer& vb, const OpenGLVertexBufferLayout& layout)
	{
		// Bind the vertex array
		this->bind();
		// Bind the vertex buffer & setup the layout
		vb.bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& elem = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.getStride(), (const void*)offset));
			offset += elem.count * VertexBufferElement::getSizeOfType(elem.type);
		}
	}

	void OpenGLVertexArray::bind() const
	{
		GLCall(glBindVertexArray(rendererId));
	}

	void OpenGLVertexArray::unbind() const
	{
		GLCall(glBindVertexArray(0));

	}

}