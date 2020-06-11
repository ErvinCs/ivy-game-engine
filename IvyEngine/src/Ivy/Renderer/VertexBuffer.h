#pragma once

#include "VertexBufferLayout.h"

namespace Ivy 
{
	/**
	 * Base class for the vertex buffer implemented per API.
	 * Provides abstract methods to set the vertex data, its layout as well as binding and unbinding it.
	 */
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		/**
		 * Bind this vertex buffer.
		 */
		virtual void bind() const = 0;
		/**
		 * Unbind this vertex buffer
		 */
		virtual void unbind() const = 0;

		/**
		 * @returns VertexBufferLayout
		 * @see VertexBufferLayout
		 */
		virtual const VertexBufferLayout& getLayout() const = 0;
		/**
		 * Set the layout of this vertex buffer
		 * @param layout VertexBufferLayout
		 */
		virtual void setLayout(const VertexBufferLayout& layout) = 0;

		/**
		 * Set the data of this vertex buffer.
		 * @param void* pointer to the vertex data
		 * @param size of the vertex data
		 */
		virtual void setData(const void* data, uint32_t size) = 0;

		/**
		 * Create a new concrete VertexBuffer depending on the used render API.
		 * @param float* vertices of the vertex buffer
		 * @param size of the vertex data (i.e. the number of floats in `vertices`
		 * @returns shared_ptr<VertexBuffer> pointing to the actual VertexBuffer
		 */
		static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);

		/**
		 * Create a new concrete VertexBuffer depending on the used render API.
		 * @param size of the vertex data (i.e. the number of floats in `vertices`
		 * @returns shared_ptr<VertexBuffer> pointing to the actual VertexBuffer
		 */
		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
	};

}