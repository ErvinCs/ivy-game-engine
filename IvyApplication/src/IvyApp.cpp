#include <Ivy.h>
#include "Ivy/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "UserComponent.h"

class TestLayer : public Ivy::SortingLayer
{
private:
	//Systems
	std::shared_ptr<Ivy::System> renderSystem    = std::make_shared<Ivy::RenderSystem>(Ivy::ECS::getInstance().getEntities());
	std::shared_ptr<Ivy::System> scriptSystem    = std::make_shared<Ivy::ScriptSystem>(Ivy::ECS::getInstance().getEntities());
	std::shared_ptr<Ivy::System> collisionSystem = std::make_shared<Ivy::CollisionSystem>(Ivy::ECS::getInstance().getEntities());
	std::shared_ptr<Ivy::System> collisionGizmos = std::make_shared<Ivy::CollidableGizmoSystem>(Ivy::ECS::getInstance().getEntities());
	std::shared_ptr<Ivy::System> userSystem      = std::make_shared<UserComponentSystem>(Ivy::ECS::getInstance().getEntities());


private:
	//Camera
	Ivy::OrthoCamera camera;

	// Screen Borders - Used for ImGui
	float leftBorder = 12.3f;
	float rightBorder = -11.8f;
	float topBorder = 6.4f;
	float botBorder = -6.4f;

public:
	TestLayer() : SortingLayer("Test"), camera(-12.8f, 12.8f, -6.4f, 6.4f)
	{
		IVY_TRACE("Creating TestLayer");
		
		Ivy::ECS::getInstance().loadEntities();

		Ivy::ECS::getInstance().addSystem(renderSystem);
		Ivy::ECS::getInstance().addSystem(scriptSystem);
		Ivy::ECS::getInstance().addSystem(collisionSystem);
		Ivy::ECS::getInstance().addSystem(collisionGizmos);
		Ivy::ECS::getInstance().addSystem(userSystem);

		renderSystem->init();
		collisionSystem->init();
		collisionGizmos->init();
		scriptSystem->init();
		userSystem->init();

		Ivy::JSONManager::addLoadFunction(loadUC);
		Ivy::JSONManager::addSaveFunction(saveUC);
	}

	void update(Ivy::Timestep ts) override
	{
		// Render
		Ivy::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		Ivy::RenderCommand::clear();
		Ivy::Renderer::Begin(camera);
		renderSystem->update(ts);
		collisionGizmos->update(ts);
		Ivy::Renderer::End();

		// Script
		scriptSystem->update(ts);

		collisionSystem->update(ts);

		// User System
		userSystem->update(ts);
	}

	void imGuiRender() override
	{
		static std::string tagTemp;
		ImGui::Begin("User Components");
		for (Entity& entity : Ivy::ECS::getInstance().getEntities())
		{
			ImGui::PushID(&entity);
			if (Ivy::ECS::getInstance().getComponent<Ivy::Tag>(entity).getComponentId() == 
				Ivy::ECS::getInstance().getComponentTypes().find(typeid(Ivy::Tag).name())->second
				&& tagTemp.size() > 0)
			{
				tagTemp = Ivy::ECS::getInstance().getComponent<Ivy::Tag>(entity).tag;
			}
			else
			{
				tagTemp = "Entity##";
			}

			if (ImGui::CollapsingHeader(tagTemp.c_str()))
			{
				if (ImGui::TreeNode("UserComp"))
				{
					if (Ivy::ECS::getInstance().getComponent<UserComponent>(entity).getComponentId() == UserCompID)
					{
						ImGui::InputFloat("aField", (float*)&Ivy::ECS::getInstance().getComponent<UserComponent>(entity).aField, 2);
						if (ImGui::Button("Remove UserComp"))
						{
							Ivy::ECS::getInstance().removeComponent<UserComponent>(entity);
							IVY_INFO("Destroyed UserComponent on Entity: {0}", entity);
						}
					}
					else
					{
						if (ImGui::Button("Add UserComp"))
						{
							UserComponent newUserComp = UserComponent(0.001f, "Hello World");
							newUserComp.setComponentId(UserCompID);
							Ivy::ECS::getInstance().addComponent<UserComponent>(entity, newUserComp);
							IVY_INFO("Added: User Component");
						}
					}
					ImGui::TreePop();
				}
			}
			ImGui::PopID();
		}
		ImGui::End();

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

