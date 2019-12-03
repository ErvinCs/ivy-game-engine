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

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererId);
		indexBuffer->bind();

		this->indexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const OpenGLVertexBufferLayout& layout)
	{
		// Bind the vertex array
		this->bind();
		// Bind the vertex buffer & setup the layout
		vb->bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& elem = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.getStride(), (const void*)offset));
			offset += elem.count * OpenGLVertexBufferElement::getSizeOfType(elem.type);
		}

		// TODO: pass in as a param a shared_ptr vb
		this->vertexBuffers.push_back(std::make_shared<OpenGLVertexBuffer>(vb));
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