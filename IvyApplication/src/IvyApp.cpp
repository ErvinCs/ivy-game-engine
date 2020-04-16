#include <Ivy.h>
#include "Ivy/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "UserComponent.h"

class TestLayer : public Ivy::SortingLayer
{
private:
	//Systems
	std::shared_ptr<Ivy::System> userSystem      = std::make_shared<UserComponentSystem>(Ivy::ECS::getInstance().getEntities());

	Ivy::OrthoCamera camera;
public:
	TestLayer() : SortingLayer("Test")
	{
		IVY_TRACE("Creating TestLayer");

		camera = Ivy::Application::GetCamera();

		Ivy::ECS::getInstance().addSystem(userSystem);

		userSystem->init();

		Ivy::JSONManager::addLoadFunction(loadUC);
		Ivy::JSONManager::addSaveFunction(saveUC);
	}

	void update(Ivy::Timestep ts) override
	{
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

