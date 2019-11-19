#pragma once

namespace Ivy {

	class OpenGLVertexBuffer
	{
	private:
		uint32_t rendererId;

	public:
		OpenGLVertexBuffer() = default;
		OpenGLVertexBuffer(const void* data, uint32_t size);
		~OpenGLVertexBuffer();

		void bind() const;
		void unbind() const;
	};

}