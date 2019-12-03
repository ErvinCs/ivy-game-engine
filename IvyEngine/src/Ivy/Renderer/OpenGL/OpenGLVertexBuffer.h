#pragma once

#include "../VertexBuffer.h"

namespace Ivy {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t rendererId;

	public:
		OpenGLVertexBuffer() = default;
		// Consider changing void* to float*
		OpenGLVertexBuffer(const void* data, uint32_t size);
		~OpenGLVertexBuffer();

		void bind() const override;
		void unbind() const override;
	};

}