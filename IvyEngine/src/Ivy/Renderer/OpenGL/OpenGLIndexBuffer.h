#pragma once

namespace Ivy {

	class OpenGLIndexBuffer
	{
	private:
		unsigned int rendererId;
		unsigned int count;

	public:
		OpenGLIndexBuffer(const unsigned int* data, unsigned int count);
		~OpenGLIndexBuffer();

		void bind() const;
		void unbind() const;

		inline unsigned int getCount() const { return count; }
	};

}