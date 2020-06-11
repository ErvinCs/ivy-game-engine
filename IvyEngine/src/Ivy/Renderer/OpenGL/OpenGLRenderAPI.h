#pragma once

#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLIndexBuffer.h"

#include "../RenderAPI.h"

#include <glad/glad.h>

// Issue a breakpoint if `x` is not true
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Simple log of render errors
void GLClearError();
// Provides a detailed log of any error that occured
bool GLLogCall(const char* function, const char* file, int line);

namespace Ivy 
{
	/**
	 * OpenGL implementation of the RenderAPI.
	 * @see RenderAPI
	 */
	class OpenGLRenderAPI : public RenderAPI
	{
	public:
		OpenGLRenderAPI() = default;
		~OpenGLRenderAPI() = default;

		/**
		 * Enable fragment blending and the depth buffer.
		 */
		void init() override;

		/**
		 * Clear scene data
		 */
		void clear() override;

		/**
		 * Issue a draw call to OpenGL
		 * @param vertexArray pointer to the VertexArray used for the draw call
		 * @see VertexArray
		 */
		void draw(const std::shared_ptr<VertexArray>& va, uint32_t indexCount = 0) override;

		/**
		 * Modify the viewport.
		 * @param x viewport center x-coordinate
		 * @param y viewport center y-coordinate
		 * @param width of the viewport
		 * @param height of the viewport
		 */
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		/**
		 * Set the color used to clear the screen.
		 * @param color vec4 RGBA color
		 */
		void setClearColor(const glm::vec4& color) override;
	};

}