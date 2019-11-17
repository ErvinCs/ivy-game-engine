#pragma once

#include "../glad/include/glad/glad.h"
#include <vector>

#include "OpenGLRenderer.h"

namespace Ivy {

	struct OpenGLVertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int getSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
			default:
				break;
			}
			ASSERT(false);
			return 0;

		}
	};

	class OpenGLVertexBufferLayout
	{
	private:
		std::vector<OpenGLVertexBufferElement> elements;
		uint32_t stride;
	public:
		OpenGLVertexBufferLayout(uint32_t stride) : stride(stride) {}
		OpenGLVertexBufferLayout() : stride(0) {}
		~OpenGLVertexBufferLayout() = default;

		// TODO: Support for more types
		template <typename T>
		void push(uint32_t count)
		{
			static_assert(false);
		}

		template<>
		void push<float>(uint32_t count)
		{
			elements.push_back({ GL_FLOAT, count, GL_FALSE });
			stride += count * OpenGLVertexBufferElement::getSizeOfType(GL_FLOAT);
		}

		template<>
		void push<uint32_t>(uint32_t count)
		{
			elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			stride += count * OpenGLVertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void push<char>(uint32_t count)
		{
			elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			stride += count * OpenGLVertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline uint32_t getStride() const { return stride; }
		inline const std::vector<OpenGLVertexBufferElement> getElements() const { return elements; }
	};

}