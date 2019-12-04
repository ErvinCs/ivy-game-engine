#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "OrthoCamera.h"
#include "RenderCommand.h"

namespace Ivy {

	class Renderer
	{
	public:
		static void init();
		static void begin(OrthoCamera& camera);
		static void end();
		static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RenderAPI::API GetAPI() { return RenderAPI::getAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 viewProjMatrix;
		};

		static SceneData* sceneData;
	};

}