#pragma once

#include "OpenGLVertexBuffer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"

//#include "OpenGLRenderer.h" - Cyclic dependency
#include "../RenderAPI.h"

namespace Ivy 
{

	/*
	 *
	 */
	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t rendererId;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
		uint32_t vbIndex = 0;
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return vertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }
	};

}