#pragma once

#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "OrthoCamera.h"
#include "RenderCommand.h"

#include <glm/glm.hpp>

namespace Ivy 
{
	/**
	 * Static class used to render the scene.
	 * Issues draw calls to the actual render API and is in charge of binding vertex arrays, shaders and textures.
	 */
	class Renderer
	{
	private:
		// Texture used to render entities whose texture's are invalid
		static std::shared_ptr<Texture> textureBlank;
	public:
		/**
		 * Create vertex buffers, index buffers and bind the default texture.
		 * Also bind the shader used to render the scene
		 */
		static void Init();

		/**
		 * Bind the shader and set the viewProjection uniform.
		 * @see OrthoCamera
		 */
		static void Begin(OrthoCamera& camera);

		/**
		 * Finish rendering the current scene.
		 */
		static void End();

		/**
		 * Shutdown the renderer.
		 */
		static void Shutdown();

		/**
		 * Draw a colored rectangle at the given position having the given size.
		 */
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		/**
		 * Draw a colored rectangle at the given position having the given size and rotation
		 */
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		/**
		 * Draw a textured rectangle at the given position having the given size.
		 */
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture);

		/**
		 * Draw a textured rectangle at the given position having the given size and rotation
		 */
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture>& texture, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

		/**
		 * @returns API the current render API
		 * @see RenderAPI
		 */
		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
	};

}