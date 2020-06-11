#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Ivy 
{
	/**
	 * Abstract class for the rendering API.
	 * Provides abstract initialization and draw methods as well as viewport manipulation methods.
	 */
	class RenderAPI
	{
	public:
		/**
		 * Enumeration of the supported render APIs.
		 */
		enum class API
		{
			None = 0, 
			OpenGL = 1
		};
	public:
		/**
		 * Initalize the renderer.
		 */
		virtual void init() = 0;

		/**
		 * Clear the screen.
		 */
		virtual void clear() = 0;

		/**
		 * Set the color used to clear the screen
		 * @param color vec4 RGBA color
		 */
		virtual void setClearColor(const glm::vec4& color) = 0;

		/**
		 * Set the viewport.
		 * @param x viewport center x-coordinate
		 * @param y viewport center y-coordinate
		 * @param width of the viewport
		 * @param height of the viewport
		 */
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/**
		 * Issue a draw call.
		 * @param vertexArray pointer to the VertexArray used for the next draw call
		 * @param indexCount int equal to the number of indices in the bound IndexBuffer used for the next draw call
		 * @see VertexArray
		 * @see IndexBuffer
		 */
		virtual void draw(const std::shared_ptr<VertexArray>& va, uint32_t indexCount = 0) = 0;

		/**
		 * @returns API the used RenderAPI
		 * @see RenderAPI
		 */
		inline static API GetAPI() { return rAPI; }

		/**
		 * @return unique_ptr<RenderAPI> pointing to the chosen RenderAPI
		 */
		static std::unique_ptr<RenderAPI> Create();
	private:
		// The used RenderAPI
		static API rAPI;
	};

}