#pragma once

#include "../IndexBuffer.h"

namespace Ivy {

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t rendererId;
		uint32_t count;

	public:
		OpenGLIndexBuffer() = default;
		OpenGLIndexBuffer(const uint32_t* data, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void bind() const override;
		void unbind() const override;

		inline uint32_t getCount() const override { return count; }
	};

}