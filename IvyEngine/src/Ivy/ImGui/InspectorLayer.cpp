#include "ivypch.h"
#include "InspectorLayer.h"

#include "../Core/Logger.h"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "../ECS/ECS.h"
#include "../ECS/Entity.h"
#include "../ECS/Component.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/Renderable.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/Tag.h"
#include "../ECS/JSONManager.h"

#include "../Scripting/ScriptManager.h"


namespace Ivy {
	using ECSPTR = ECS & (*)(void);
	ECSPTR getECS = &ECS::getInstance;

	void InspectorLayer::imGuiRender()
	{
		static std::string pngPathTemp;
		static std::string tagTemp, newTagTemp;
		for (Entity& entity : getECS().getEntities()) {
			ImGui::PushID(&entity);
			// -------------------- Display Tag --------------------
			if (getECS().getComponent<Tag>(entity).getComponentId() == uint8_t(3) && tagTemp.size() > 0)
			{
				tagTemp = getECS().getComponent<Tag>(entity).tag;
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
						ImGui::InputTextWithHint("Tag", tagTemp.c_str(), &newTagTemp);
						if (ImGui::Button("Rename Tag"))
						{
							getECS().getComponent<Tag>(entity).tag = newTagTemp;
							newTagTemp = "";
						}
					}
					else
					{
						ImGui::InputText("Tag", &newTagTemp);
						if (ImGui::Button("Add Tag"))
						{
							if (newTagTemp.size() > 2) {
								Tag newTag = Tag(newTagTemp);
								newTag.setComponentId(3);
								getECS().addComponent<Tag>(entity, newTag);
								newTagTemp = "";
								IVY_INFO("Added: Tag={0}", newTagTemp);
							}
						}
					}
					if (ImGui::Button("Remove Tag"))
					{
						getECS().removeComponent<Tag>(entity);
						IVY_INFO("Destroyed Tag on Entity: {0}", entity);
					}
					ImGui::TreePop();
				}

				// -------------------- Transform --------------------
				if (ImGui::TreeNode("Transform"))
				{
					if (getECS().getComponent<Transform>(entity).getComponentId() == uint8_t(0))
					{
						ImGui::InputFloat2("Position", (float*)&getECS().getComponent<Transform>(entity).position, 2);
						ImGui::InputFloat2("Scale", (float*)&getECS().getComponent<Transform>(entity).scale, 2);
						ImGui::InputFloat("Rotation", (float*)&getECS().getComponent<Transform>(entity).rotation, 2);
					}
					else
					{
						if (ImGui::Button("Add Transform"))
						{
							Transform newTransfrom = Transform(glm::vec2(1, 1), 0, glm::vec2(1, 1));
							newTransfrom.setComponentId(0);
							getECS().addComponent<Transform>(entity, newTransfrom);
							IVY_INFO("Added: Transform=({0},{1}), ({2}, {3}), {4}",
								getECS().getComponent<Transform>(entity).position.x,
								getECS().getComponent<Transform>(entity).position.y,
								getECS().getComponent<Transform>(entity).scale.x,
								getECS().getComponent<Transform>(entity).scale.y,
								getECS().getComponent<Transform>(entity).rotation);
						}
					}
					if (ImGui::Button("Remove Transform"))
					{
						getECS().removeComponent<Transform>(entity);
						IVY_INFO("Destroyed Transform on Entity: {0}", entity);
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
						}
					}
					else
					{
						ImGui::InputText("PNG Path", &pngPathTemp);
						if (ImGui::Button("Add Renderable"))
						{
							if (pngPathTemp.size() > 2) {
								Renderable newRenderable = Renderable(pngPathTemp);
								newRenderable.setComponentId(1);
								getECS().addComponent<Renderable>(entity, newRenderable);
								pngPathTemp = "";
								IVY_INFO("Added: Renderable Sprite Path={0}", getECS().getComponent<Renderable>(entity).spritePath);
							}
						}
					}
					if (ImGui::Button("Remove Renderable"))
					{
						getECS().removeComponent<Renderable>(entity);
						IVY_INFO("Destroyed Renderable on Entity: {0}", entity);
					}
					ImGui::TreePop();
				}

				// -------------------- Script --------------------
				if (ImGui::TreeNode("Script")) {
					if (getECS().getComponent<ScriptComponent>(entity).getComponentId() == uint8_t(2))
					{
						const char* currentPath = getECS().getComponent<ScriptComponent>(entity).scriptName.c_str();
						std::string* buffer = &getECS().getComponent<ScriptComponent>(entity).scriptName;
						ImGui::InputTextWithHint("Script Path", currentPath, buffer);
						if (ImGui::Button("Import Script"))
						{
							getECS().getComponent<ScriptComponent>(entity).scriptName = *buffer;
							ScriptManager::GetInstance().createScriptController(
								getECS().getComponent<ScriptComponent>(entity).scriptName,
								&getECS().getComponent<ScriptComponent>(entity).scriptableObject,
								entity);
						}
					}
					else
					{
						if (ImGui::Button("Add Script"))
						{
							ScriptComponent newScript = ScriptComponent();
							newScript.setComponentId(2);
							getECS().addComponent<ScriptComponent>(entity, newScript);
							IVY_INFO("Added: Script Path={0}", getECS().getComponent<ScriptComponent>(entity).scriptName);
						}
					}
					if (ImGui::Button("Remove Script"))
					{
						getECS().removeComponent<ScriptComponent>(entity);
						IVY_INFO("Destroyed Script on Entity: {0}", entity);
					}
					ImGui::TreePop();
				}

				// -------------------- Delete Entity --------------------
				if (ImGui::Button("Delete Entity"))
				{
					getECS().destroyEntity(entity);
					IVY_INFO("Destroyed Entity: {0}", entity);
				}
			}
			ImGui::PopID();
		}
		if (ImGui::Button("New Entity"))
		{
			Entity entity = getECS().createEntity();
			IVY_INFO("Created Entity#{0}", entity);
		}
		if (ImGui::Button("Save"))
		{
			JSONManager::SaveEntities(Paths::entitiesRepoPath.string());
			IVY_INFO("Entities saved. Location: {0}", Paths::entitiesRepoPath.string());
		}
	}
}