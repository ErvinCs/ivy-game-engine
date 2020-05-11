#pragma once

namespace Ivy 
{
	/*
	 *
	 */
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static std::shared_ptr<IndexBuffer> Create(uint32_t* data, uint32_t size);
	};

}