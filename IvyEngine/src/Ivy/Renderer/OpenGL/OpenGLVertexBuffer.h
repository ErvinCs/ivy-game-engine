#pragma once

namespace Ivy {

	class OpenGLVertexBuffer
	{
	private:
		unsigned int rendererId;

	public:
		OpenGLVertexBuffer(const void* data, unsigned int size);
		~OpenGLVertexBuffer();

		void bind() const;
		void unbind() const;
	};

}