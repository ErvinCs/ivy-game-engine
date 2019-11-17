#pragma once

namespace Ivy {

	class OpenGLIndexBuffer
	{
	private:
		uint32_t rendererId;
		uint32_t count;

	public:
		OpenGLIndexBuffer(const uint32_t* data, uint32_t count);
		~OpenGLIndexBuffer();

		void bind() const;
		void unbind() const;

		inline uint32_t getCount() const { return count; }
	};

}