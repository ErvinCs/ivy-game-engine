#pragma once

#include "RenderAPI.h"

namespace Ivy {

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

		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			renderAPI->drawIndexed(vertexArray);
		}
	private:
		static RenderAPI* renderAPI;
	};

}