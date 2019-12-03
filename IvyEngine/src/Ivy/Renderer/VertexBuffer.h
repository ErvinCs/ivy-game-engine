#pragma once

namespace Ivy {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		// void* to float* ?
		static VertexBuffer* Create(void* vertices, uint32_t size);
	};

}