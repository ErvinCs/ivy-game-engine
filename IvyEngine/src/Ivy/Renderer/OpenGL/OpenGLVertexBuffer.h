#pragma once

#include "../VertexBuffer.h"

namespace Ivy {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t rendererId;
		VertexBufferLayout layout;
	public:
		OpenGLVertexBuffer() = default;
		// Consider changing void* to float*
		OpenGLVertexBuffer(const float* data, uint32_t size);
		~OpenGLVertexBuffer();

		virtual const VertexBufferLayout& getLayout() const override { return layout; }
		virtual void setLayout(const VertexBufferLayout& layout) override { this->layout = layout; }

		void bind() const override;
		void unbind() const override;
	};

}