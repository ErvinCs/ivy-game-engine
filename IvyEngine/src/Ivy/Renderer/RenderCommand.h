#pragma once

#include "RenderAPI.h"

namespace Ivy 
{
	/**
	 * Static class used to issue commands to the Renderer through the used render API
	 */
	class RenderCommand
	{
	public:

		/**
		 * Calls `init` for the used render API. 
		 */
		inline static void init()
		{
			renderAPI->init();
		}

		/**
		 * Calls `setClearColor` for the used render API. This will set the color used to clear the screen.
		 * @param color vec4 RGBA color
		 */
		inline static void setClearColor(const glm::vec4& color)
		{
			renderAPI->setClearColor(color);
		}

		/**
		 * Calls `clear` for the used render API. This will clear the screen.
		 */
		inline static void clear()
		{
			renderAPI->clear();
		}

		/**
		 * Calls `Draw` for the used render API. This will issue a draw call
		 * @param vertexArray pointer to the VertexArray used for the draw call
		 * @see VertexArray
		 */
		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray)
		{
			renderAPI->draw(vertexArray);
		}

		/**
		 * Calls `SetViewport` for the used render API. This will modify the viewport.
		 * @param x viewport center x-coordinate
		 * @param y viewport center y-coordinate
		 * @param width of the viewport
		 * @param height of the viewport
		 */
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			renderAPI->setViewport(x, y, width, height);
		}
	private:
		// Points to the actual RenderAPI
		static std::unique_ptr<RenderAPI> renderAPI;
	};

}