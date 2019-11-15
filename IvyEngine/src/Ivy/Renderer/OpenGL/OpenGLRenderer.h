#pragma once

#include <gl/GL.h>

#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLIndexBuffer.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

//TODO - Define a BufferElement

namespace Ivy {

	// Will not make a singleton
	// Use case: multiple layers that need multiple renderers
	class OpenGLRenderer
	{
	public:
		void clear() const;
		void draw(const OpenGLVertexArray& va, const OpenGLIndexBuffer& ib, const OpenGLShader& shader) const;
	};

}