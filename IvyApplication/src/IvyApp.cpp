#include <Ivy.h>

#include "imgui/imgui.h"

class TestLayer : public Ivy::SortingLayer
{
private:
	std::shared_ptr<Ivy::Texture> playerTexture;
	std::shared_ptr<Ivy::Texture> tileTexture;
	std::shared_ptr<Ivy::Texture> pictureTex;
	glm::vec4 playerColor;
	glm::vec2 playerSize;
	glm::vec2 picturePosition;
	glm::vec2 playerPosition;
	glm::vec2 tilePosition;
	glm::vec2 tileSize;
	float playerMoveSpeed = 5.0f;

	Ivy::OrthoCamera camera;
	glm::vec3 cameraPos;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;

private:
	bool isJumping = false;
	bool isFalling = false;
	const float constJumpTime = 1.3f;
	const float jumpSpeed = 2.0f;
	float jumpTime = constJumpTime;
	float jumpCooldown = 1.0f;

	float leftBorder = 12.3f;
	float rightBorder = -11.8f;
	float topBorder = 6.4f;
	float botBorder = -6.4f;

public:
	TestLayer() : SortingLayer("Test"), camera(-12.8f, 12.8f, -6.4f, 6.4f), cameraPos({ 0.0f, 4.0f, 0.0f })
	{
		IVY_TRACE("Creating TestLayer");
		playerTexture = Ivy::Texture::Create("C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\ninja.png");
		tileTexture = Ivy::Texture::Create("C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png");
		pictureTex = Ivy::Texture::Create("C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\cat1.png");
		playerColor = glm::vec4({ 255.0f, 0.0f, 0.0f, 255.0f });
		playerPosition = glm::vec2({ 0.0f, -3.6f });
		tilePosition = glm::vec2({ 2.0f, 2.0f });
		playerSize = glm::vec2({ 3.0f, 3.0f });
		tileSize = glm::vec2({ 1.0f, 1.0f });
		picturePosition = glm::vec2(11.5f, 5.4f);
	}

	void update(Ivy::Timestep ts) override
	{
		//IVY_TRACE("Update:  timestep={0}", ts);
		jumpCooldown -= ts;

		if (Ivy::InputHandler::IsKeyDown(IVY_KEY_D))
		{
			//IVY_TRACE("KeyD down");
			if (playerPosition.x < leftBorder)
			{
				playerPosition.x += playerMoveSpeed * ts;
			}
		}
		else if (Ivy::InputHandler::IsKeyDown(IVY_KEY_A))
		{
			//IVY_TRACE("KeyA down");
			if (playerPosition.x > rightBorder)
			{
				playerPosition.x -= playerMoveSpeed * ts;
			}
		}

		if (Ivy::InputHandler::IsKeyDown(IVY_KEY_W))
		{
			if (!isJumping && jumpCooldown <= 0)
			{
				isJumping = true;
			}
		}

		if (isJumping)
		{
			jumpTime -= ts;
			if (jumpTime > constJumpTime / 2)	
			{
				// isRising
				playerPosition.y += playerMoveSpeed * ts * jumpSpeed;
			}
			else if (jumpTime < constJumpTime / 2 && jumpTime > 0)
			{
				// isFalling
				playerPosition.y -= playerMoveSpeed * ts * jumpSpeed;
			}
			else
			{
				// Reset
				isJumping = false;
				jumpCooldown = 1.0f;
				jumpTime = constJumpTime;
			}
		} 

		// Render
		Ivy::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		Ivy::RenderCommand::clear();

		Ivy::Renderer::Begin(camera);

		Ivy::Renderer::DrawRect(playerPosition, playerSize, playerTexture);
		Ivy::Renderer::DrawRect(playerPosition, playerSize + glm::vec2(0.5f, 0.5f), playerColor);
		for (int i = -20; i < 20; i++)
		{
			Ivy::Renderer::DrawRect(tilePosition + glm::vec2(i, -8.0f), tileSize, tileTexture);
		}
		Ivy::Renderer::DrawRect(picturePosition, glm::vec2(2.0f, 2.0f), pictureTex);

		Ivy::Renderer::End();
	}

	void imGuiRender() override
	{
		ImGui::SliderFloat(" Position X", &playerPosition.x, leftBorder, rightBorder);
		ImGui::SliderFloat(" Position Y", &playerPosition.y, botBorder, topBorder);
		ImGui::SliderFloat(" Size X", &playerSize.x, leftBorder, rightBorder);
		ImGui::SliderFloat(" Size Y", &playerSize.y, botBorder, topBorder);
		ImGui::SliderFloat(" Position X Cat", &picturePosition.x, leftBorder, rightBorder);
		ImGui::SliderFloat(" Position Y Cat", &picturePosition.y, botBorder, topBorder);
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