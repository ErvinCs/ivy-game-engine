#pragma once

#include "../VertexBuffer.h"

namespace Ivy {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t rendererId;
		VertexBufferLayout layout;

	public:
		//OpenGLVertexBuffer() = default;
		OpenGLVertexBuffer(const float* data, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual const VertexBufferLayout& getLayout() const override { return layout; }
		virtual void setLayout(const VertexBufferLayout& layout) override { this->layout = layout; }

		virtual void bind() const override;
		virtual void unbind() const override;
	};

}