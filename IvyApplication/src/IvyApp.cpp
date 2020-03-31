#include <Ivy.h>

#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

using ECS = Ivy::ECS&(*)(void);
using Transform = Ivy::Transform;
using Renderable = Ivy::Renderable;
using Script = Ivy::ScriptComponent;
using Tag = Ivy::Tag;

/* TODOs
 - Remove hardcoded strings - use <filesystem>
 - Collision System ( + Events )
 - PCG Module

 - Move ImGui code to the engine side
 - Place entities on Rendering Sorting Layers
 - Remove Explicit camera creation from IvyApp - Move it to engine side and allow acces to it
 - Remove Explicit system init from IvyApp - Move it to engine side
 - Centralize Component IDs

 - Prompt before terminating application & Auto-save state on shutdown
 - Enable AngelScript Leak Checking ( in EntryPoint )
 - Fix JSONManager & Renderer issues
*/

class TestLayer : public Ivy::SortingLayer
{
private:
	ECS getECS = &Ivy::ECS::getInstance;

	//Systems
	std::shared_ptr<Ivy::System> renderSystem = std::make_shared<Ivy::RenderSystem>(getECS().getEntities());
	std::shared_ptr<Ivy::System> scriptSystem = std::make_shared<Ivy::ScriptSystem>(getECS().getEntities());

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
		
		getECS().loadEntities();

		getECS().addSystem(renderSystem);
		getECS().addSystem(scriptSystem);

		renderSystem->init();
		scriptSystem->init();		
	}

	void update(Ivy::Timestep ts) override
	{
		// Render
		Ivy::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		Ivy::RenderCommand::clear();
		Ivy::Renderer::Begin(camera);
		renderSystem->update(ts);
		Ivy::Renderer::End();

		// Script
		scriptSystem->update(ts);
	}

	void imGuiRender() override
	{
		static std::string pathTemp;
		static std::string tagTemp;
		for (Entity& entity : getECS().getEntities()) {
			ImGui::PushID(&entity);
			// -------------------- Display Tag --------------------
			if (getECS().getComponent<Tag>(entity).getComponentId() == uint8_t(3))
			{
				tagTemp = getECS().getComponent<Tag>(entity).tag;
				if (tagTemp.size() <= 2)
					tagTemp = "Entity##";
			}
			else
			{
				tagTemp = "Entity##";
			}

			if (ImGui::CollapsingHeader(tagTemp.c_str()))
			{
				// -------------------- Tag --------------------
				if (ImGui::TreeNode("Tag"))
				{
					if (getECS().getComponent<Tag>(entity).getComponentId() == uint8_t(3))
					{
						ImGui::InputText("Tag", &pathTemp);
						if (ImGui::Button("Rename Tag"))
						{
							getECS().getComponent<Tag>(entity).tag = pathTemp;
							IVY_INFO("Updated Tag={0}", getECS().getComponent<Tag>(entity).tag);
							pathTemp = "";
						}
					}
					else
					{
						ImGui::InputText("Tag", &pathTemp);
						if (ImGui::Button("Add Tag"))
						{
							if (pathTemp.size() > 2) {
								Tag newTag = Tag(pathTemp);
								newTag.setComponentId(3);
								getECS().addComponent<Tag>(entity, newTag);
								pathTemp = "";
							}
						}
					}
					ImGui::TreePop();
				}

				// -------------------- Transform --------------------
				if (ImGui::TreeNode("Transform")) 
				{
					if (getECS().getComponent<Transform>(entity).getComponentId() == uint8_t(0))
					{
							ImGui::SliderFloat2("Position##", (float*)&getECS().getComponent<Transform>(entity).position, leftBorder, rightBorder);
							ImGui::SliderFloat2("Size##", (float*)&getECS().getComponent<Transform>(entity).scale, 1.0f, 30.0f);
							ImGui::SliderFloat("Rotation##", &getECS().getComponent<Transform>(entity).rotation, 0.0f, 2.0f * 3.1415f);
					}
					else 
					{
						if (ImGui::Button("Add Transform"))
						{
							Transform newTransfrom = Transform(glm::vec2(1, 1), 0, glm::vec2(1,1));
							newTransfrom.setComponentId(0);
							getECS().addComponent<Transform>(entity, newTransfrom);
						}
					}
					ImGui::TreePop();
				}

				// -------------------- Renderable --------------------
				if (ImGui::TreeNode("Renderable")) 
				{
					const char* currentPath = nullptr;
					std::string* buffer = nullptr;
					if (getECS().getComponent<Renderable>(entity).getComponentId() == uint8_t(1))
					{
						currentPath = getECS().getComponent<Renderable>(entity).spritePath.c_str();
						buffer = &getECS().getComponent<Renderable>(entity).spritePath;
						ImGui::InputTextWithHint("PNG Path", currentPath, buffer);	
						if (ImGui::Button("Import PNG"))
						{
							getECS().getComponent<Renderable>(entity).spritePath = *buffer;
							getECS().getComponent<Renderable>(entity).texture = Ivy::Texture::Create(*buffer);
							IVY_INFO("Updated Renderable SpritePath={0}", getECS().getComponent<Renderable>(entity).spritePath);
						}
					}
					else
					{
						ImGui::InputText("PNG Path", &pathTemp);
						if (ImGui::Button("Add Renderable"))
						{
							IVY_INFO("Add Renderable BufferSize={0}", pathTemp.size());
							if (pathTemp.size() > 2) {
								Renderable newRenderable = Renderable(pathTemp);
								newRenderable.setComponentId(1);
								getECS().addComponent<Renderable>(entity, newRenderable);
								pathTemp = "";
							}
						}
					}	
					ImGui::TreePop();
				}

				// -------------------- Script --------------------
				if (ImGui::TreeNode("Script")) {
					if (getECS().getComponent<Script>(entity).getComponentId() == uint8_t(2))
					{
						const char* currentPath = getECS().getComponent<Script>(entity).scriptName.c_str();
						std::string* buffer = &getECS().getComponent<Script>(entity).scriptName;
						ImGui::InputTextWithHint("Script Path", currentPath, buffer);
						if (ImGui::Button("Import Script"))
						{
							getECS().getComponent<Script>(entity).scriptName = *buffer;
							Ivy::ScriptManager::GetInstance().createScriptController(
								getECS().getComponent<Script>(entity).scriptName, 
								&getECS().getComponent<Script>(entity).scriptableObject,
								entity);
							IVY_INFO("Update: *Buffer={0}, ScriptName={1}", *buffer, getECS().getComponent<Script>(entity).scriptName);
						}
					}
					else
					{
						if (ImGui::Button("Add Script"))
						{
							Script newScript = Script();
							newScript.setComponentId(2);
							getECS().addComponent<Script>(entity, newScript);
						}
					}
					ImGui::TreePop();
				}

				// -------------------- Delete Entity --------------------
				if (ImGui::Button("Delete Entity"))
				{
					getECS().destroyEntity(entity);
				}
			}
			ImGui::PopID();
		}
		if (ImGui::Button("New Entity"))
		{
			getECS().createEntity();
		}
		if (ImGui::Button("Save"))
		{
			Ivy::JSONManager::SaveEntities(getECS().entitiesRepoPath);
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

