#pragma once

#include "../VertexBuffer.h"

namespace Ivy 
{
	/**
	 * An OpenGL VertexBuffer used to store vertex draw data and its layout.
	 * @see VertexBufferLayout
	 * @see VertexBuffer
	 */
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		uint32_t rendererId;
		VertexBufferLayout layout;

	public:
		/**
		 * Creates an array buffer of the given `size` containing the passed `data`. 
		 * Issues a static draw call. (The data store contents will be modified once and used many times)
		 */
		OpenGLVertexBuffer(float* data, uint32_t size);
		
		/**
		 * Creates an array buffer of the given `size`. Issues a dynamic draw call.
		 * Issues a dynamic draw call. (The data store contents will be modified repeatedly and used many times)
		 */
		OpenGLVertexBuffer(uint32_t size);

		virtual ~OpenGLVertexBuffer();

		/**
		 * @returns VertexBufferLayout
		 */
		virtual const VertexBufferLayout& getLayout() const override { return layout; }
		
		/**
		 * @param layout VertexBufferLayout
		 */
		virtual void setLayout(const VertexBufferLayout& layout) override { this->layout = layout; }

		/**
		 * Binds the draw `data` having the given `size`.
		 */
		virtual void setData(const void* data, uint32_t size) override;

		/**
		 * Bind the VertexBuffer.
		 */
		virtual void bind() const override;

		/**
		 * Unbind the VertexBuffer.
		 */
		virtual void unbind() const override;
	};

}