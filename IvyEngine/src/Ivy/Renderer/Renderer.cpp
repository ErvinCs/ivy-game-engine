#include "ivypch.h"
#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"
#include "../Core/Logger.h"
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/ResourcePaths.h"
namespace Ivy 
{
	std::shared_ptr<Texture> Renderer::textureBlank;
	struct RenderData
	{
		std::shared_ptr<VertexArray> vertexArray;
		std::shared_ptr<Shader> shaderTex;
	};
	static RenderData data;

	void Renderer::Init()
	{
		RenderCommand::init();

		data = RenderData();
		data.vertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		vb->setLayout({
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float2, "texCoord" }
			});
		data.vertexArray->addVertexBuffer(vb);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		data.vertexArray->setIndexBuffer(ib);

		textureBlank = Texture::Create(Paths::BASE_TEXTURE_PATH.string(), true);

		IVY_CORE_INFO("Loading shader from location: {0}", Paths::SHADER_PATH);
		data.shaderTex = Shader::Create(Paths::SHADER_PATH.string());
		data.shaderTex->bind();
		data.shaderTex->setUniform1i("u_texture", 0);
	}

	void Renderer::Begin(OrthoCamera& camera)
	{
		data.shaderTex->bind();
		data.shaderTex->setUniformMat4f("u_viewProjection", camera.getViewProjMatrix());
	}

	void Renderer::End()
	{
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		data.shaderTex->setUniform4f("u_color", color);
		textureBlank->bind();

		glm::vec3 position3 = glm::vec3(position.x, position.y, 0.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position3) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data.shaderTex->setUniformMat4f("u_transform", transform);
		data.vertexArray->bind();
		RenderCommand::Draw(data.vertexArray);
	}

	void Renderer::DrawRect(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		data.shaderTex->setUniform4f("u_color", color);
		textureBlank->bind();

		glm::vec3 position3 = glm::vec3(position.x, position.y, 0.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position3) 
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data.shaderTex->setUniformMat4f("u_transform", transform);
		data.vertexArray->bind();
		RenderCommand::Draw(data.vertexArray);
	}

	void Renderer::DrawRect(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture)
	{
		data.shaderTex->setUniform4f("u_color", glm::vec4(1.0f));
		texture->bind();

		glm::vec3 position3 = glm::vec3(position.x, position.y, 0.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position3) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data.shaderTex->setUniformMat4f("u_transform", transform);

		data.vertexArray->bind();
		RenderCommand::Draw(data.vertexArray);
	}

	void Renderer::DrawRect(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture>& texture, const glm::vec4& color)
	{
		data.shaderTex->setUniform4f("u_color", color);
		texture->bind();

		glm::vec3 position3 = glm::vec3(position.x, position.y, 0.0f);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position3)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data.shaderTex->setUniformMat4f("u_transform", transform);
		data.vertexArray->bind();
		RenderCommand::Draw(data.vertexArray);
	}

}