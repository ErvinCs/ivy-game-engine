#include "ivypch.h"
#include "JSONManager.h"

#include <json.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "ECS.h"
#include "../Core/Logger.h"

using Json = nlohmann::json;
namespace Ivy {

	void JSONManager::SaveEntities(const std::string& path) {
		IVY_INFO("JSONManager: Saving entities to location: {0}", path);

		Json jsonNull;
		Json finalObject;

		std::ofstream writer(path);

		EntityContainer container = ECS::getInstance().getEntities();
		std::vector<Entity> freeContainer = ECS::getInstance().getEntities().getFreeEntities();
		uint16_t entryCounter = 0;
		for (Entity& entity : container)
		{
			IVY_CORE_INFO("JSONManager: Writing Entity={0}", entity);

			Json jsonObject;
			jsonObject["entity_id"] = entity;
			
			
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

			if(ECS::getInstance().getComponent<Renderable>(entity).getEntityId() != entity)
			{
				jsonObject["components"]["renderable"] = jsonNull;
			} 
			else {
				jsonObject["components"]["renderable"] = ECS::getInstance().getComponent<Renderable>(entity).spritePath;
			}

			if(ECS::getInstance().getComponent<ScriptComponent>(entity).getEntityId() != entity)
			{
				jsonObject["components"]["script"] = jsonNull;
			}
			else {
				jsonObject["components"]["script"] = ECS::getInstance().getComponent<ScriptComponent>(entity).scriptName;
			}

			if (ECS::getInstance().getComponent<Tag>(entity).getEntityId() != entity)
			{
				jsonObject["components"]["tag"] = jsonNull;
			}
			else {
				jsonObject["components"]["tag"] = ECS::getInstance().getComponent<Tag>(entity).tag;
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
				std::vector<Entity> freeEntities{};
				current["free"].get_to(freeEntities);
				for (auto it = freeEntities.begin(); it != freeEntities.end(); it++)
				{
					ECS::getInstance().addToFreeEntities(*it);
				}
			}
			else
			{
				uint16_t entityId;
				current["entity_id"].get_to(entityId);
				ECS::getInstance().addToEntities(entityId);

				Entity entity = ECS::getInstance().getEntities().getEntity(entityId);

				IVY_CORE_INFO("JSONManager: Loading Entity={0}", entity);

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

				if (!current["components"]["renderable"].is_null())
				{
					std::string renderablePath;
					current["components"]["renderable"].get_to(renderablePath);
					Renderable renderable{ renderablePath };
					ECS::getInstance().addComponent<Renderable>(entity, renderable);
				}

				if (!current["components"]["script"].is_null())
				{
					std::string scriptPath;
					current["components"]["script"].get_to(scriptPath);
					ScriptComponent script{ scriptPath };
					script.setEntityId(entity);
					ECS::getInstance().addComponent<ScriptComponent>(entity, script);
				}

				if (!current["components"]["tag"].is_null())
				{
					std::string tagName;
					current["components"]["tag"].get_to(tagName);
					Tag tag{ tagName };
					ECS::getInstance().addComponent<Tag>(entity, tag);
				}
			}
		}
	}

}