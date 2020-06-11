#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

namespace Ivy 
{
	/**
	 * Base class for the Vertex Array implemented per API.
	 * Provides functionality to add vertex buffers and set the index buffer used to render them.
	 */
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		
		/**
		 * Add a vertex buffer
		 * @param vb pointer to the vertex buffer to be added
		 */
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) = 0;	

		/**
		 * Set the index buffer used to render the data provided by the vertex buffers
		 * @param indexBuffer pointer to the index buffer to be set
		 */
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		/**
		 * Bind the vertex array.
		 */
		virtual void bind() const = 0;

		/**
		 * Unbind the vertex array
		 */
		virtual void unbind() const = 0;

		/**
		 * @returns vector<std::shared_ptr<VertexBuffer>>& the collection of vertex buffers used to render
		 */
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;

		/**
		 * @returns shared_ptr<IndexBuffer>& the index buffer used to render
		 */
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;


		/**
		 * Creates a new concrete Vertex Array depending on the used render API.
		 * @returns shared_ptr<VertexArray> pointing to the VertexArray
		 */
		static std::shared_ptr<VertexArray> Create();
	};

}