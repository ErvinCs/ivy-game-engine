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

		virtual void setData(const void* data, uint32_t size) = 0;

		static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
	};

}