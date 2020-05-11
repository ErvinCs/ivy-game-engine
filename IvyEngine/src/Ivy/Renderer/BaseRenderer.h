#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "OrthoCamera.h"
#include "RenderCommand.h"

#include <glm/glm.hpp>

namespace Ivy 
{
	/*
	 *
	 */
	class BaseRenderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

		struct SceneData
		{
			glm::mat4 viewProjMatrix;
		};

		static std::unique_ptr<SceneData> sceneData;
	};

}