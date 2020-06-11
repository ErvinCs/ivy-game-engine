#pragma once

namespace Ivy 
{
	/**
	 * Abstract index buffer.
	 * Provides abstract methods to access to the number of indices used  to render a texture
	 */
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		/**
		 * Bind the index buffer.
		 */
		virtual void bind() const = 0;

		/**
		 * Unvind the index buffer.
		 */
		virtual void unbind() const = 0;

		/**
		 * @returns uint32_t the number of allocated uint32_ts (indices)
		 */
		virtual uint32_t getCount() const = 0;

		/**
		 * Create a new concrete IndexBuffer depending on the used render API.
		 * @param data uint32_t pointer to the render data
		 * @param size uint32_t the number of uint32_ts to allocate
		 */
		static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t size);
	};

}