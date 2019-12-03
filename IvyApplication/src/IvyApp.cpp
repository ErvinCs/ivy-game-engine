#include <Ivy.h>

#include "imgui/imgui.h"

//TODO
class TestLayer : public Ivy::SortingLayer
{
private:
	std::shared_ptr<Ivy::Shader> shader;// ("res_temp/shaders/test.shader");
	std::shared_ptr<Ivy::VertexArray> va;

	Ivy::OrthoCamera camera;
	glm::vec3 cameraPos;
	float cameraMoveSpeed = 5.0f;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;

public:
	TestLayer() : SortingLayer("Test"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPos(0.0f) 
	{
		va.reset(Ivy::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Ivy::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Ivy::VertexBuffer::Create(vertices, sizeof(vertices)));
		Ivy::VertexBufferLayout layout = {
			{ Ivy::ShaderDataType::Float3, "a_Position" },
			{ Ivy::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->setLayout(layout);
		va->addVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Ivy::IndexBuffer> indexBuffer;
		indexBuffer.reset(Ivy::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		va->setIndexBuffer(indexBuffer);

		shader = Ivy::Shader::Create("res_temp/shaders/test.shader");
	}

	void update(Ivy::Timestep ts) override
	{
		//IVY_INFO("TestLayer Client Update.");
		if (Ivy::InputHandler::IsKeyDown(IVY_KEY_A))
		{
			cameraPos.x -= cameraMoveSpeed * ts;
		}
		else if (Ivy::InputHandler::IsKeyDown(IVY_KEY_D))
		{
			cameraPos.x += cameraMoveSpeed * ts;
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
		//IVY_INFO("Test Layer: {0}", event.toString());
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