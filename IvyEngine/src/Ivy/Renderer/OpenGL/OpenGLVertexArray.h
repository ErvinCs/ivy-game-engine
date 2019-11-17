#pragma once

#include "OpenGLVertexBuffer.h"
#include "OpenGLRenderer.h"

namespace Ivy {

	/*
	 * Forward decalred VertexBufferLayout
	 *  such that it does not need to be included here
	 *  to avoid cyclic dependency in Renderer
	 */
	class OpenGLVertexBufferLayout;


	class OpenGLVertexArray
	{
	private:
		uint32_t rendererId;
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void addVertexBuffer(const OpenGLVertexBuffer& vb, const OpenGLVertexBufferLayout& layout);
		void bind() const;
		void unbind() const;
	};

}