#pragma once

#include "VertexBufferLayout.h"

namespace Ivy {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const VertexBufferLayout& getLayout() const = 0;
		virtual void setLayout(const VertexBufferLayout& layout) = 0;

		// void* to float* ?
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

}