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
		unsigned int rendererId;
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void addBuffer(const OpenGLVertexBuffer& vb, const OpenGLVertexBufferLayout& layout);
		void bind() const;
		void unbind() const;
	};

}