#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"


namespace Ivy {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		/////////// TEMP ///////////////
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const OpenGLVertexBufferLayout& layout) = 0;
		//////////////////////////////// TODO: Use Base-class parameters
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}