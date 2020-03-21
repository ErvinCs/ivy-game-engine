#include <Ivy.h>

#include "imgui/imgui.h"

using ECS = Ivy::ECS&(*)(void);
using Transform = Ivy::Transform;
using Renderable = Ivy::Renderable;
using Script = Ivy::ScriptComponent;

class TestLayer : public Ivy::SortingLayer
{
private:
	ECS getECS = &Ivy::ECS::getInstance;

	void InitEntity(Entity& entity, Transform& transform) {
		getECS().addComponent<Transform>(entity, transform);
	}

	void InitEntity(Entity& entity, Renderable& renderable) {
		getECS().addComponent<Renderable>(entity, renderable);
	}

	void InitEntity(Entity& entity, Transform& transform, Renderable& renderable) {
		getECS().addComponent<Transform>(entity, transform);
		getECS().addComponent<Renderable>(entity, renderable);
	}

	void InitEntity(Entity& entity, Transform& transform, Renderable& renderable, Script& script) {
		getECS().addComponent<Transform>(entity, transform);
		getECS().addComponent<Renderable>(entity, renderable);
		getECS().addComponent<Script>(entity, script);
	}

private:
	// Entities
	Entity player = getECS().createEntity();
	Transform playerTransform{ glm::vec2(0.0f, -3.6f), 0.0f, glm::vec2(2.0f, 2.0f) }; 		
	Renderable playerRenderable{ "C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\ninja.png" };
	Script playerScript{ "C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\scripts\\player.as" };

	const int noTiles = 20;
	std::array<Entity, 20> tiles = {
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity(),
		getECS().createEntity()

	};
	std::array<Transform, 20> transforms = {
		Transform(glm::vec2(-11.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-10.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-9.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-8.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-7.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-6.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-5.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-4.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-3.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-2.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(-1.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(0.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(1.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(2.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(3.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(4.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(5.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(6.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(7.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
		Transform(glm::vec2(8.0f, -5.6f), 0.0f, glm::vec2(1.0f, 1.0f)),
	};
	std::array<Renderable, 20> renderables = {
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png",
		"C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\tile.png"
	};

	Entity sprite = getECS().createEntity();
	Transform spriteTransform{ glm::vec2(0.0f, 2.0f), 180.0f, glm::vec2(2.0f, 2.0f) };
	Renderable spriteRenderable{ "C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\sprite.png" };
	Script spriteScript{ "C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\scripts\\patrol.as" };

	Entity cat = getECS().createEntity();;
	Transform catTransform{ glm::vec2(11.5f, 5.4f), 0.0f, glm::vec2(2.0f, 2.0f) };
	Renderable catRenderable{ "C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\cat1.png" };

	//Systems
	std::shared_ptr<Ivy::System> renderSystem = std::make_shared<Ivy::RenderSystem>(getECS().getEntities());
	std::shared_ptr<Ivy::System> scriptSystem = std::make_shared<Ivy::ScriptSystem>(getECS().getEntities());

private:
	//Camera
	Ivy::OrthoCamera camera;
	glm::vec3 cameraPos;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;

	// Screen Borders - Used for ImGui
	float leftBorder = 12.3f;
	float rightBorder = -11.8f;
	float topBorder = 6.4f;
	float botBorder = -6.4f;

public:
	TestLayer() : SortingLayer("Test"), camera(-12.8f, 12.8f, -6.4f, 6.4f), cameraPos({ 0.0f, 4.0f, 0.0f })
	{
		IVY_TRACE("Creating TestLayer");

		//TODO - THIS: player = getECS().createEntity();

		InitEntity(player, playerTransform, playerRenderable, playerScript);
		InitEntity(sprite, spriteTransform, spriteRenderable, spriteScript);
		InitEntity(cat, catTransform, catRenderable);

		for (int i = 0; i < noTiles; i++)
		{
			InitEntity(tiles[i], transforms[i], renderables[i]);
		}
		
		getECS().addSystem(renderSystem);
		getECS().addSystem(scriptSystem);

		renderSystem->init();
		scriptSystem->init();
	}

	void update(Ivy::Timestep ts) override
	{
		// Render
		Ivy::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });
		Ivy::RenderCommand::clear();
		Ivy::Renderer::Begin(camera);
		renderSystem->update(ts);
		Ivy::Renderer::End();

		// Script
		scriptSystem->update(ts);
	}

	void imGuiRender() override
	{
		ImGui::SliderFloat(" Position X Player", &getECS().getComponent<Transform>(player).position.x, leftBorder, rightBorder);
		ImGui::SliderFloat(" Position Y Player", &getECS().getComponent<Transform>(player).position.y, leftBorder, rightBorder);
		ImGui::SliderFloat(" Size X Player",     &getECS().getComponent<Transform>(player).scale.x, leftBorder, rightBorder);
		ImGui::SliderFloat(" Size Y Player",     &getECS().getComponent<Transform>(player).scale.y, leftBorder, rightBorder);
		ImGui::SliderFloat(" Rotation Player",   &getECS().getComponent<Transform>(player).rotation, 0.0f, 360.0f);
		ImGui::SliderFloat(" Position X Cat",    &getECS().getComponent<Transform>(cat).position.x, leftBorder, rightBorder);
		ImGui::SliderFloat(" Position Y Cat",    &getECS().getComponent<Transform>(cat).position.y, leftBorder, rightBorder);
		ImGui::SliderFloat(" Position X Sprite", &getECS().getComponent<Transform>(sprite).position.x, leftBorder, rightBorder);
		ImGui::SliderFloat(" Position Y Sprite", &getECS().getComponent<Transform>(sprite).position.y, botBorder, topBorder);

	}

	void onEvent(Ivy::Event& event) override
	{
		IVY_INFO("Test Layer: {0}", event.toString());
	}

	~TestLayer()
	{
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