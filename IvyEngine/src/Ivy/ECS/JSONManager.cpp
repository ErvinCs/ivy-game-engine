#include "ivypch.h"
#include "JSONManager.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "ECS.h"
#include "EntityContainer.h"
#include "../Core/Logger.h"
#include "../Core//Application.h"
#include "../Renderer/OrthoCamera.h"


namespace Ivy {
	using Json = nlohmann::json;

	std::vector<std::function<void(Entity&, nlohmann::json&)>> JSONManager::SaveFunctions;
	std::vector<std::function<void(Entity&, nlohmann::json&)>> JSONManager::LoadFunctions;


	void saveTransform(Entity& entity, Json& jsonObject)
	{
		Json jsonNull;
		if (ECS::getInstance().getComponent<Transform>(entity).getEntityId() != entity)
		{
			jsonObject["components"]["transform"] = jsonNull;
		}
		else {
			Transform transform = ECS::getInstance().getComponent<Transform>(entity);
			jsonObject["components"]["transform"]["positionX"] = transform.position.x;
			jsonObject["components"]["transform"]["positionY"] = transform.position.y;
			jsonObject["components"]["transform"]["rotation"] = transform.rotation;
			jsonObject["components"]["transform"]["scaleX"] = transform.scale.x;
			jsonObject["components"]["transform"]["scaleY"] = transform.scale.y;
		}
	}

	void saveRenderable(Entity& entity, Json& jsonObject)
	{
		Json jsonNull;
		if (ECS::getInstance().getComponent<Renderable>(entity).getEntityId() != entity)
		{
			jsonObject["components"]["renderable"] = jsonNull;
		}
		else {
			jsonObject["components"]["renderable"] = ECS::getInstance().getComponent<Renderable>(entity).spritePath;
		}
	}

	void saveScriptComponent(Entity& entity, Json& jsonObject)
	{
		Json jsonNull;
		if (ECS::getInstance().getComponent<ScriptComponent>(entity).getEntityId() != entity)
		{
			jsonObject["components"]["script"] = jsonNull;
		}
		else {
			jsonObject["components"]["script"] = ECS::getInstance().getComponent<ScriptComponent>(entity).scriptName;
		}
	}

	void saveTag(Entity& entity, Json& jsonObject)
	{
		Json jsonNull;
		if (ECS::getInstance().getComponent<Tag>(entity).getEntityId() != entity)
		{
			jsonObject["components"]["tag"] = jsonNull;
		}
		else {
			jsonObject["components"]["tag"] = ECS::getInstance().getComponent<Tag>(entity).tag;
		}
	}

	void saveCollidableBox(Entity& entity, Json& jsonObject)
	{
		Json jsonNull;
		if (ECS::getInstance().getComponent<CollidableBox>(entity).getEntityId() != entity)
		{
			jsonObject["components"]["collidable_box"] = jsonNull;
		}
		else {
			CollidableBox collidable = ECS::getInstance().getComponent<CollidableBox>(entity);
			jsonObject["components"]["collidable_box"]["centerPositionX"] = collidable.centerPosition.x;
			jsonObject["components"]["collidable_box"]["centerPositionY"] = collidable.centerPosition.y;
			jsonObject["components"]["collidable_box"]["rotation"] = collidable.rotation;
			jsonObject["components"]["collidable_box"]["halfScaleX"] = collidable.halfScale.x;
			jsonObject["components"]["collidable_box"]["halfScaleY"] = collidable.halfScale.y;
			jsonObject["components"]["collidable_box"]["is_trigger"] = collidable.isTrigger;
		}
	}

	void loadCollidableBox(Entity& entity, Json& current)
	{
		if (!current["components"]["collidable_box"].is_null())
		{
			float posX, posY, rotation, halfScaleX, halfScaleY;
			bool isTrigger;
			current["components"]["collidable_box"]["centerPositionX"].get_to(posX);
			current["components"]["collidable_box"]["centerPositionY"].get_to(posY);
			current["components"]["collidable_box"]["rotation"].get_to(rotation);
			current["components"]["collidable_box"]["halfScaleX"].get_to(halfScaleX);
			current["components"]["collidable_box"]["halfScaleY"].get_to(halfScaleY);
			current["components"]["collidable_box"]["is_trigger"].get_to(isTrigger);
			CollidableBox collidable{ glm::vec2(posX, posY), rotation, glm::vec2(halfScaleX, halfScaleY) };
			collidable.isTrigger = isTrigger;
			ECS::getInstance().addComponent<CollidableBox>(entity, collidable);

		}
	}

	void loadTransform(Entity& entity, Json& current)
	{
		if (!current["components"]["transform"].is_null())
		{
			float posX, posY, rotation, scaleX, scaleY;
			current["components"]["transform"]["positionX"].get_to(posX);
			current["components"]["transform"]["positionY"].get_to(posY);
			current["components"]["transform"]["rotation"].get_to(rotation);
			current["components"]["transform"]["scaleX"].get_to(scaleX);
			current["components"]["transform"]["scaleY"].get_to(scaleY);
			Transform transform{ glm::vec2(posX, posY), rotation, glm::vec2(scaleX, scaleY) };
			ECS::getInstance().addComponent<Transform>(entity, transform);

		}
	}

	void loadRenderable(Entity& entity, Json& current)
	{
		if (!current["components"]["renderable"].is_null())
		{
			std::string renderablePath;
			current["components"]["renderable"].get_to(renderablePath);
			Renderable renderable{ renderablePath };
			ECS::getInstance().addComponent<Renderable>(entity, renderable);
		}
	}

	void loadScriptComponent(Entity& entity, Json& current)
	{
		if (!current["components"]["script"].is_null())
		{
			std::string scriptPath;
			current["components"]["script"].get_to(scriptPath);
			ScriptComponent script{ scriptPath };
			script.setEntityId(entity);
			ECS::getInstance().addComponent<ScriptComponent>(entity, script);
		}
	}

	void loadTag(Entity& entity, Json& current)
	{
		if (!current["components"]["tag"].is_null())
		{
			std::string tagName;
			current["components"]["tag"].get_to(tagName);
			Tag tag{ tagName };
			ECS::getInstance().addComponent<Tag>(entity, tag);
		}
	}

	void JSONManager::SaveEntities(const std::string& path) {
		IVY_INFO("JSONManager: Saving entities to location: {0}", path);

		Json jsonNull;
		Json finalObject;

		std::ofstream writer(path);

		EntityContainer container = ECS::getInstance().getEntities();
		std::unordered_set<Entity> freeContainer = ECS::getInstance().getEntities().getFreeEntities();
		uint16_t entryCounter = 0;
		for (Entity& entity : container)
		{
			IVY_CORE_INFO("JSONManager: Writing Entity={0}", entity);

			Json jsonObject;
			jsonObject["entity_id"] = entity;
			
			for (auto& func : SaveFunctions)
			{
				func(entity, jsonObject);
			}

			finalObject[entryCounter] = jsonObject;
			entryCounter++;
		}

		Json jsonFree;
		if (freeContainer.empty())
			jsonFree["free"] = jsonNull;
		else {
			jsonFree["free"] = freeContainer;
		}
		finalObject[entryCounter] = jsonFree;

		writer << std::setw(2) << finalObject << std::endl;
		writer.close();
	}

	void JSONManager::LoadCamera(const std::string & path)
	{
		IVY_INFO("JSONManager: Loading camera from location: {0}", path);

		std::ifstream reader(path);
		Json json;
		reader >> json;
		reader.close();

		float posX, posY, posZ, rotation;
		int owner;
		json["camera"]["position_x"].get_to(posX);
		json["camera"]["position_y"].get_to(posY);
		json["camera"]["position_z"].get_to(posZ);
		json["camera"]["rotation"].get_to(rotation);
		json["camera"]["owner"].get_to(owner);
		Application::GetCamera().setPosition(glm::vec3(posX, posY, posZ));
		Application::GetCamera().setRotation(rotation);
		Application::GetCamera().setOwner(owner);
	}

	void JSONManager::SaveCamera(const std::string & path)
	{
		IVY_INFO("JSONManager: Saving camera to location: {0}", path);

		Json jsonObject;

		std::ofstream writer(path);

		OrthoCamera camera = Application::GetCamera();

		jsonObject["camera"]["position_x"] = camera.getPosition().x;
		jsonObject["camera"]["position_y"] = camera.getPosition().y;
		jsonObject["camera"]["position_z"] = camera.getPosition().z;
		jsonObject["camera"]["rotation"]   = camera.getRotation();
		jsonObject["camera"]["owner"] = camera.getOwner();

		writer << std::setw(2) << jsonObject << std::endl;
		writer.close();
	}

	void JSONManager::AddLoadFunction(std::function<void(Entity&, nlohmann::json&)> func)
	{
		JSONManager::LoadFunctions.push_back(func);
	}

	void JSONManager::AddSaveFunction(std::function<void(Entity&, nlohmann::json&)> func)
	{
		JSONManager::SaveFunctions.push_back(func);
	}

	void JSONManager::InitFunctions()
	{
		SaveFunctions.push_back(saveTransform);
		SaveFunctions.push_back(saveRenderable);
		SaveFunctions.push_back(saveScriptComponent);
		SaveFunctions.push_back(saveTag);
		SaveFunctions.push_back(saveCollidableBox);

		LoadFunctions.push_back(loadTransform);
		LoadFunctions.push_back(loadRenderable);
		LoadFunctions.push_back(loadScriptComponent);
		LoadFunctions.push_back(loadTag);
		LoadFunctions.push_back(loadCollidableBox);
	}

	void JSONManager::LoadEntities(const std::string& path) {
		IVY_CORE_INFO("JSONManager: Loading entities from location: {0}", path);

		std::ifstream reader(path);
		Json json;
		reader >> json;
		reader.close();
		
		for (auto& it = json.begin(); it != json.end(); ++it)
		{
			auto& current = *it;

			if (!current["free"].is_null())
			{
				IVY_CORE_INFO("JSONManager: Loading Free Entities");
				std::vector<Entity> freeEntities{};
				current["free"].get_to(freeEntities);
				for (auto it = freeEntities.begin(); it != freeEntities.end(); it++)
				{
					ECS::getInstance().addToFreeEntities(*it);
				}
			}
			else if (!current["entity_id"].is_null())
			{
				uint16_t entityId;
				current["entity_id"].get_to(entityId);
				ECS::getInstance().addToEntities(entityId);

				Entity entity = ECS::getInstance().getEntities().getEntity(entityId);

				IVY_CORE_INFO("JSONManager: Loading Entity={0}", entity);

				for (auto& func : LoadFunctions)
				{
					func(entity, current);
				}
			}
		}
	}
}