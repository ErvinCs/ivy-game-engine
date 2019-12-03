#pragma once

#include "OpenGLVertexBuffer.h"
#include "../VertexArray.h"
//#include "OpenGLRenderer.h" - Cyclic dependency

namespace Ivy {

	/*
	 * Forward decalred VertexBufferLayout
	 *  such that it does not need to be included here
	 *  to avoid cyclic dependency in Renderer
	 */
	class OpenGLVertexBufferLayout;

	// TODO
	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t rendererId;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const OpenGLVertexBufferLayout& layout) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual void bind() const override;
		virtual void unbind() const override;


		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }
	};

}