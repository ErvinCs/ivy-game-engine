#pragma once

#include "../IndexBuffer.h"

namespace Ivy 
{
	/**
	 * OpenGL implementation of the IndexBuffer.
	 * Provides access to the number of indices used  to render a texture
	 * @see IndexBuffer
	 */
	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		uint32_t rendererId;
		uint32_t count;

	public:
		/**
		 * Set the buffer data to `data` and allocate `count` unit32_ts.
		 */
		OpenGLIndexBuffer(const uint32_t* data, uint32_t count);

		virtual ~OpenGLIndexBuffer();

		/**
		 * Bind the index buffer.
		 */
		virtual void bind() const override;

		/**
		 * Unbind the index buffer
		 */
		virtual void unbind() const override;

		/**
		 * @returns uint32_t the number of allocated uint32_ts (indices)
		 */
		inline virtual uint32_t getCount() const override { return count; }
	};

}