#include "ivypch.h"
#include "OpenGLVertexArray.h"

#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Ivy {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Ivy::ShaderDataType::Float:    return GL_FLOAT;
		case Ivy::ShaderDataType::Float2:   return GL_FLOAT;
		case Ivy::ShaderDataType::Float3:   return GL_FLOAT;
		case Ivy::ShaderDataType::Float4:   return GL_FLOAT;
		case Ivy::ShaderDataType::Mat3:     return GL_FLOAT;
		case Ivy::ShaderDataType::Mat4:     return GL_FLOAT;
		case Ivy::ShaderDataType::Int:      return GL_INT;
		case Ivy::ShaderDataType::Int2:     return GL_INT;
		case Ivy::ShaderDataType::Int3:     return GL_INT;
		case Ivy::ShaderDataType::Int4:     return GL_INT;
		case Ivy::ShaderDataType::Bool:     return GL_BOOL;
		}

		return 0;	// Unkonw data type
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		GLCall(
		glGenVertexArrays(1, &rendererId);
		);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		GLCall(
		glDeleteVertexArrays(1, &rendererId);
		);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererId);
		indexBuffer->bind();

		this->indexBuffer = indexBuffer;
	}

	//void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const OpenGLVertexBufferLayout& layout)
	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb)	//, const std::shared_ptr<VertexBufferLayout>& layou
	{
		// Bind the vertex array
		this->bind();
		// Bind the vertex buffer & setup the layout
		vb->bind();
		const auto& elements = vb->getLayout();
		for(const auto& element : elements)
		{
			glEnableVertexAttribArray(vbIndex);
			glVertexAttribPointer(vbIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				elements.GetStride(),
				(const void*)element.Offset);
			vbIndex++;
		}

		this->vertexBuffers.push_back(vb);
	}

	void OpenGLVertexArray::bind() const
	{
		GLCall(
		glBindVertexArray(rendererId);
		);
	}

	void OpenGLVertexArray::unbind() const
	{
		GLCall(
		glBindVertexArray(0);
		);

	}



}