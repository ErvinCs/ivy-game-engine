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

	Entity platform = getECS().createEntity();
	Renderable platformRenderable{ "C:\\Workspace\\ivy-game-engine\\IvyEngine\\res_temp\\textures\\platform-20.png" };
	Transform platformTransform{ glm::vec2(0.0f, -5.6f), 0.0f, glm::vec2(20.0f, 1.0f) };

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

		InitEntity(player, playerTransform, playerRenderable, playerScript);
		InitEntity(sprite, spriteTransform, spriteRenderable, spriteScript);
		InitEntity(cat, catTransform, catRenderable);
		InitEntity(platform, platformTransform, platformRenderable);
		
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
		/* TODOs
		 - Hookup an InputText for Renderable Path - foreach Entity
		 - Hookup an Input text for Script Path - foreach Entity
		 - Create Entity Button - outside collapsing headers
		 - Add Component Button - foreach Entity
		*/
		for (Entity& entity : getECS().getEntities()) {
			ImGui::PushID(&entity);
			if (ImGui::CollapsingHeader("Entity##"))
			{
				ImGui::SliderFloat2("Position" + entity, (float*)&getECS().getComponent<Transform>(entity).position, leftBorder, rightBorder);
				ImGui::SliderFloat2("Size" + entity, (float*)&getECS().getComponent<Transform>(entity).scale, 1.0f, 30.0f);
				ImGui::SliderFloat("Rotation" + entity, &getECS().getComponent<Transform>(entity).rotation, 0.0f, 2.0f * 3.1415f);
			}
			ImGui::PopID();
		}
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