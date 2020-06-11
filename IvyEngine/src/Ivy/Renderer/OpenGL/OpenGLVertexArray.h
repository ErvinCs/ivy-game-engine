#pragma once

#include "OpenGLVertexBuffer.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"

#include "../RenderAPI.h"

namespace Ivy 
{

	/**
	 * An OpenGL VertexArray encapsulating an IndexBuffer and associated VertexBuffers.
	 * @see VertexArray
	 */
	class OpenGLVertexArray : public VertexArray
	{
	private:
		uint32_t rendererId;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
		uint32_t vbIndex = 0;
	public:

		/**
		 * Create a Vertex Array.
		 */
		OpenGLVertexArray();
		
		/**
		 * Delete the Vertex Array.
		 */
		virtual ~OpenGLVertexArray();

		/**
		 * Add a VertexBuffer to the collection of buffers associated with this array (and with its index buffer).
		 * @param vb pointer to the VertexBuffer to be added
		 */
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) override;

		/**
		 * Set the IndexBuffer used by this VertexArray.
		 * @param indexBuffer the new IndexBuffer
		 * @see OpenGLIndexBuffer
		 */
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		/**
		 * Bind this Vertex Array.
		 */
		virtual void bind() const override;

		/**
		 * Unbind this Vertex Array.
		 */
		virtual void unbind() const override;

		/**
		 * @returns the collection vertex buffers of this vertex array
		 */
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return vertexBuffers; }

		/**
		 * @returns the index buffer of this vertex array
		 */
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return indexBuffer; }


	};

}