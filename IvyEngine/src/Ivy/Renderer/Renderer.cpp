#include "ivypch.h"
#include "Renderer.h"

namespace Ivy {

	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;

	void Renderer::init()
	{
		RenderCommand::init();
	}

	void Renderer::begin(OrthoCamera& camera)
	{
		sceneData->viewProjMatrix = camera.getViewProjMatrix();
	}

	void Renderer::end()
	{
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		// TODO
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4f("u_vpm", sceneData->viewProjMatrix);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}


}