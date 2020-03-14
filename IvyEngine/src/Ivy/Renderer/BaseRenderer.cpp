#include "ivypch.h"
#include "BaseRenderer.h"

#include "Renderer.h"

namespace Ivy {

	std::unique_ptr<BaseRenderer::SceneData> BaseRenderer::sceneData = std::make_unique<BaseRenderer::SceneData>();

	void BaseRenderer::Init()
	{
		RenderCommand::init();
		Renderer::Init();
	}

	void BaseRenderer::Shutdown()
	{
		Renderer::Shutdown();
	}

	void BaseRenderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void BaseRenderer::BeginScene(OrthoCamera& camera)
	{
		sceneData->viewProjMatrix = camera.getViewProjMatrix();
	}

	void BaseRenderer::EndScene()
	{
	}


	void BaseRenderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->bind();
		shader->setUniformMat4f("u_viewProjection", sceneData->viewProjMatrix);
		shader->setUniformMat4f("u_transform", transform);

		vertexArray->bind();
		RenderCommand::Draw(vertexArray);
	}

}