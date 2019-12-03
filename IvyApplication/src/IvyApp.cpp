#include <Ivy.h>

#include "imgui/imgui.h"

//TODO
class TestLayer : public Ivy::SortingLayer
{
private:
	std::shared_ptr<Ivy::Shader> shader;
	std::shared_ptr<Ivy::VertexArray> va;
	std::shared_ptr<Ivy::Texture> texture;
	Ivy::OrthoCamera camera;
	glm::vec3 cameraPos;
	float cameraMoveSpeed = 5.0f;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;

private:
	bool isJumping = false;
	const float constJumpTime = 2.0f;
	float jumpTime = constJumpTime;
	float jumpCooldown = 1.0f;

	//float leftBorder = -12.8f;
	//float rightBorder = 12.8f;
	//float topBorder = -6.4f;
	//float botBorder = 6.4f;

public:
	TestLayer() : SortingLayer("Test"), camera(-12.8f, 12.8f, -6.4f, 6.4f), cameraPos(0.0f) 
	{
		IVY_TRACE("Creating TestLayer");
		
		va.reset(Ivy::VertexArray::Create());
		float vertices[] = {
		   -0.4f,  -0.4f, 0.0f, 0.0f,	//0
			0.4f,  -0.4f, 1.0f, 0.0f,	//1
			0.4f,   0.4f, 1.0f, 1.0f,	//2
		   -0.4f,   0.4f, 0.0f, 1.0f	//3
		};
		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<Ivy::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Ivy::VertexBuffer::Create(vertices, sizeof(vertices)));
		Ivy::VertexBufferLayout layout = {
			{ Ivy::ShaderDataType::Float3, "position" },
			{ Ivy::ShaderDataType::Float2, "texCoord" }
		};
		vertexBuffer->setLayout(layout);
		va->addVertexBuffer(vertexBuffer);

		std::shared_ptr<Ivy::IndexBuffer> indexBuffer;
		indexBuffer.reset(Ivy::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		va->setIndexBuffer(indexBuffer);

		shader = Ivy::Shader::Create("C:/Workspace/ivy-game-engine/IvyEngine/res_temp/shaders/image.shader"); 
		shader->bind();
		texture = Ivy::Texture::Create("C:/Workspace/ivy-game-engine/IvyEngine/res_temp/textures/sprite.png");
		texture->bind(0);

		IVY_TRACE("Created TestLayer");
	}

	void update(Ivy::Timestep ts) override
	{
		IVY_TRACE("Update:  timestep={0}", ts);
		jumpCooldown -= ts;

		if (Ivy::InputHandler::IsKeyDown(IVY_KEY_A))
		{
			//if (cameraPos.x < leftBorder)
				cameraPos.x += cameraMoveSpeed * ts;
			IVY_TRACE("KeyA down");
		}
		else if (Ivy::InputHandler::IsKeyDown(IVY_KEY_D))
		{
			//if (cameraPos.x < rightBorder)
				cameraPos.x -= cameraMoveSpeed * ts;
			IVY_TRACE("KeyD down");
		}

		//TODOD - Refactor this Jump: Rise while key down, after peek is reached start falling
		if (Ivy::InputHandler::IsKeyDown(IVY_KEY_W) && jumpCooldown <= 0)
		{
			if (!isJumping)
			{
				jumpTime -= ts;
				cameraPos.y -= cameraMoveSpeed * ts;
				isJumping = true;
			}
			else if (jumpTime > constJumpTime / 2)	//Rise
			{
				jumpTime -= ts;
				//if (cameraPos.y < topBorder)
					cameraPos.y -= cameraMoveSpeed * ts;
			}
			else if (jumpTime < constJumpTime / 2 && jumpTime > 0.0f)	//Fall
			{
				jumpTime -= ts;
				//if (cameraPos.y > botBorder)
					cameraPos.y += cameraMoveSpeed * ts;
			}
			else if (jumpTime <= 0.0f)
			{
				isJumping = false;
				jumpCooldown = 1.0f;
				jumpTime = constJumpTime;
			}
			
		} 

		Ivy::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ivy::RenderCommand::clear();

		camera.setPosition(cameraPos);
		camera.setRotation(cameraRotation);

		Ivy::Renderer::begin(camera);

		Ivy::Renderer::submit(shader, va);

		Ivy::Renderer::end();
	}

	void onEvent(Ivy::Event& event) override
	{
		IVY_INFO("Test Layer: {0}", event.toString());
	}
};

class IvyApp : public Ivy::Application
{
public:
	IvyApp()
	{
		pushLayer(new TestLayer());
	}

	~IvyApp()
	{

	}
};


Ivy::Application* Ivy::CreateApp()
{
	return new IvyApp();
}