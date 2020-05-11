#pragma once

#include "RenderAPI.h"

namespace Ivy 
{
	/*
	 *
	 */
	class RenderCommand
	{
	public:
		inline static void init()
		{
			renderAPI->init();
		}

		inline static void setClearColor(const glm::vec4& color)
		{
			renderAPI->setClearColor(color);
		}

		inline static void clear()
		{
			renderAPI->clear();
		}

		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray)
		{
			renderAPI->draw(vertexArray);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			renderAPI->setViewport(x, y, width, height);
		}
	private:
		static std::unique_ptr<RenderAPI> renderAPI;
	};

}