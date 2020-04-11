#include "ivypch.h"
#include "InspectorLayer.h"

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"

#include "../Core/Logger.h"
#include "../ECS/JSONManager.h"
#include "../ECS/CollidableGizmoSystem.h"
#include "../Scripting/ScriptManager.h"


namespace Ivy {
	using ECSPTR = ECS & (*)(void);
	ECSPTR getECS = &ECS::getInstance;

	void InspectorLayer::imGuiRender()
	{
		static std::string pngPathTemp;
		static std::string tagTemp, newTagTemp;
		static std::string scriptPathTemp;
		for (Entity& entity : getECS().getEntities()) 
		{
			ImGui::PushID("Ivy: Entity#" + entity);
			// -------------------- Display Tag --------------------
			if (getECS().getComponent<Tag>(entity).getComponentId() == TagID && tagTemp.size() > 0)
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
					if (getECS().getComponent<Tag>(entity).getComponentId() == TagID)
					{
						ImGui::InputTextWithHint("Tag", tagTemp.c_str(), &newTagTemp);
						if (ImGui::Button("Rename Tag"))
						{
							getECS().getComponent<Tag>(entity).tag = newTagTemp;
							newTagTemp = "";
						}
						if (ImGui::Button("Remove Tag"))
						{
							getECS().removeComponent<Tag>(entity);
							IVY_INFO("Destroyed Tag on Entity: {0}", entity);
						}
					}
					else
					{
						ImGui::InputText("Tag", &newTagTemp);
						if (ImGui::Button("Add Tag"))
						{
							if (newTagTemp.size() > 0) {
								Tag newTag = Tag(newTagTemp);
								newTag.setComponentId(TagID);
								getECS().addComponent<Tag>(entity, newTag);
								newTagTemp = "";
								IVY_INFO("Added: Tag={0}", newTagTemp);
							}
						}
					}
					
					ImGui::TreePop();
				}

				// -------------------- Transform --------------------
				if (ImGui::TreeNode("Transform"))
				{
					if (getECS().getComponent<Transform>(entity).getComponentId() == TransformID)
					{
						ImGui::InputFloat2("Position", (float*)&getECS().getComponent<Transform>(entity).position, 2);
						ImGui::InputFloat2("Scale", (float*)&getECS().getComponent<Transform>(entity).scale, 2);
						ImGui::InputFloat("Rotation", (float*)&getECS().getComponent<Transform>(entity).rotation, 2);
						if (ImGui::Button("Remove Transform"))
						{
							getECS().removeComponent<Transform>(entity);
							IVY_INFO("Destroyed Transform on Entity: {0}", entity);
						}
					}
					else
					{
						if (ImGui::Button("Add Transform"))
						{
							Transform newTransfrom = Transform(glm::vec2(1, 1), 0, glm::vec2(1, 1));
							newTransfrom.setComponentId(TransformID);
							getECS().addComponent<Transform>(entity, newTransfrom);
							IVY_INFO("Added: Transform=({0},{1}), ({2}, {3}), {4}",
								newTransfrom.position.x,
								newTransfrom.position.y,
								newTransfrom.scale.x,
								newTransfrom.scale.y,
								newTransfrom.rotation);
						}
					}
					
					ImGui::TreePop();
				}

				// -------------------- Renderable --------------------
				if (ImGui::TreeNode("Renderable"))
				{
					const char* currentPath = nullptr;
					std::string* buffer = nullptr;
					if (getECS().getComponent<Renderable>(entity).getComponentId() == RenderableID)
					{
						currentPath = getECS().getComponent<Renderable>(entity).spritePath.c_str();
						buffer = &getECS().getComponent<Renderable>(entity).spritePath;
						ImGui::InputTextWithHint("PNG Path", currentPath, buffer);
						if (ImGui::Button("Import PNG"))
						{
							getECS().getComponent<Renderable>(entity).spritePath = *buffer;
							getECS().getComponent<Renderable>(entity).texture = Ivy::Texture::Create(*buffer);
						}
						if (ImGui::Button("Remove Renderable"))
						{
							getECS().removeComponent<Renderable>(entity);
							IVY_INFO("Destroyed Renderable on Entity: {0}", entity);
						}
					}
					else
					{
						ImGui::InputText("PNG Path", &pngPathTemp);
						if (ImGui::Button("Add Renderable"))
						{
							if (pngPathTemp.size() > 0) {
								Renderable newRenderable = Renderable(pngPathTemp);
								newRenderable.setComponentId(RenderableID);
								getECS().addComponent<Renderable>(entity, newRenderable);
								pngPathTemp = "";
								IVY_INFO("Added: Renderable Sprite Path={0}", newRenderable.spritePath);
							}
						}
					}
					
					ImGui::TreePop();
				}

				// -------------------- Script --------------------
				if (ImGui::TreeNode("Script")) 
				{
					if (getECS().getComponent<ScriptComponent>(entity).getComponentId() == ScriptComponentID)
					{
						const char* currentPath = getECS().getComponent<ScriptComponent>(entity).scriptName.c_str();
						std::string* buffer = &getECS().getComponent<ScriptComponent>(entity).scriptName;
						ImGui::InputTextWithHint("Script Path", currentPath, buffer);
						if (ImGui::Button("Import Script"))
						{
							ScriptComponent* script = &getECS().getComponent<ScriptComponent>(entity);
							getECS().removeComponent<ScriptComponent>(entity);
							ScriptComponent newScript = ScriptComponent(*buffer);
							newScript.setComponentId(ScriptComponentID);
							getECS().addComponent<ScriptComponent>(entity, newScript);
							ScriptManager::GetInstance().createScriptController(
								(Paths::scriptsPath / *buffer).string(),
								&getECS().getComponent<ScriptComponent>(entity).scriptableObject,
								entity);
						}
						if (ImGui::Button("Remove Script"))
						{
							ScriptComponent* script = &getECS().getComponent<ScriptComponent>(entity);
							getECS().removeComponent<ScriptComponent>(entity);
							IVY_INFO("Destroyed Script on Entity: {0}", entity);
						}
					}
					else
					{
						ImGui::InputText("Script Path", &scriptPathTemp);
						if (ImGui::Button("Add Script"))
						{
							if (scriptPathTemp.size() > 0) {
								ScriptComponent newScript = ScriptComponent(scriptPathTemp);
								newScript.setComponentId(ScriptComponentID);
								getECS().addComponent<ScriptComponent>(entity, newScript);
								ScriptManager::GetInstance().createScriptController(
									(Paths::scriptsPath / scriptPathTemp).string(),
									&getECS().getComponent<ScriptComponent>(entity).scriptableObject,
									entity);
								scriptPathTemp = "";
								IVY_INFO("Added: Script Name={0}, Path={1}", 
									newScript.scriptName,
									newScript.scriptableObject.getName());
							}
						}
					}					
					ImGui::TreePop();
				}

				if (ImGui::TreeNode("CollidableBox"))
				{
					if (getECS().getComponent<CollidableBox>(entity).getComponentId() == CollidableBoxID)
					{
						ImGui::Checkbox("Is Trigger", &getECS().getComponent<CollidableBox>(entity).isTrigger);
						ImGui::InputFloat2("Position", (float*)&getECS().getComponent<CollidableBox>(entity).centerPosition, 2);
						ImGui::InputFloat("Rotation", (float*)&getECS().getComponent<CollidableBox>(entity).rotation, 2);
						ImGui::InputFloat2("Scale", (float*)&getECS().getComponent<CollidableBox>(entity).halfScale, 2);
						ImGui::Text("Note that for the CollidableBox to cover the whole object");
						ImGui::Text(" it should have half the scale of the transform");
						
						//TODO: if rotation changes then update collidable
						if (ImGui::Button("Remove CollidableBox"))
						{
							getECS().removeComponent<CollidableBox>(entity);
							IVY_INFO("Destroyed CollidableBox on Entity: {0}", entity);
						}
					}
					else
					{
						if (ImGui::Button("Add CollidableBox"))
						{
							if (getECS().getComponent<Transform>(entity).getComponentId() != TransformID)
							{
								Transform newTransfrom = Transform(glm::vec2(1, 1), 0, glm::vec2(1, 1));
								newTransfrom.setComponentId(TransformID);
								getECS().addComponent<Transform>(entity, newTransfrom);
								IVY_INFO("Added: Transform=({0},{1}), ({2}, {3}), {4}",
									newTransfrom.position.x,
									newTransfrom.position.y,
									newTransfrom.scale.x,
									newTransfrom.scale.y,
									newTransfrom.rotation);
							}
							Transform transform = getECS().getComponent<Transform>(entity);
							CollidableBox newCollidable = CollidableBox(transform.position, transform.rotation, transform.scale / 2.0f);;
							newCollidable.setComponentId(CollidableBoxID);
							getECS().addComponent<CollidableBox>(entity, newCollidable);
							IVY_INFO("Added: CollidableBox=({0},{1}), ({2}, {3}), {4}, {5}",
								newCollidable.centerPosition.x,
								newCollidable.centerPosition.y,
								newCollidable.halfScale.x,
								newCollidable.halfScale.y,
								newCollidable.rotation,
								newCollidable.isTrigger);
						}
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
			IVY_INFO("Created Entity={0}", entity);
		}
		ImGui::Checkbox("Show Gizmos", &CollidableGizmoSystem::showGizmos);
		if (ImGui::Button("Save"))
		{
			JSONManager::SaveEntities(Paths::entitiesRepoPath.string());
			IVY_INFO("Entities saved. Location: {0}", Paths::entitiesRepoPath.string());
		}
	}
}