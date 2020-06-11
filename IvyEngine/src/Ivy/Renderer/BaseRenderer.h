#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "OrthoCamera.h"
#include "RenderCommand.h"

#include <glm/glm.hpp>

namespace Ivy 
{
	/**
	 * A layer of abstraction over the actual Renderer class used.
	 */
	class BaseRenderer
	{
	public:

		/**
		 * Initialize the actual Renderer and the RenderAPI
		 */
		static void Init();

		/**
		 * Shutdown the actual Renderer
		 */
		static void Shutdown();

		/**
		 * Issue a RenderCommand to resize the window
		 */
		static void OnWindowResize(uint32_t width, uint32_t height);

		/**
		 * Sets the view-projection matrix for one scene.
		 * @param camera OrthoCamera used to determine the view-projection matrix
		 */
		static void BeginScene(OrthoCamera& camera);
		
		/**
		 * Perform operations on scene end
		 */
		static void EndScene();

		/**
		 * Issue a draw call to the Renderer in use.
		 * Binds a given shader and vertex array and sets the view-projection matrix and object's transformation as uniforms.
		 * @param shader pointer to the shader used to render
		 * @param vertexArray pointer to the vertex array used to render
		 * @param transform mat4 storing the object transformation
		 * @see Shader
		 * @see VertexArray
		 */
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		/**
		 * @returns the RenderAPI to use
		 */
		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

		// Used to cache a view-projection matrix
		struct SceneData
		{
			glm::mat4 viewProjMatrix;
		};

		/**
		 * Pointer to the Renderer scene data
		 */
		static std::unique_ptr<SceneData> sceneData;
	};

}