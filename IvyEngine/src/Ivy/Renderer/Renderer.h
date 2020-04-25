#pragma once

#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "OrthoCamera.h"
#include "RenderCommand.h"

#include <glm/glm.hpp>

namespace Ivy {

	class Renderer
	{
	private:
		static std::shared_ptr<Texture> textureBlank;
	public:
		static void Init();
		static void Begin(OrthoCamera& camera);
		static void End();
		static void Shutdown();
		
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};

}