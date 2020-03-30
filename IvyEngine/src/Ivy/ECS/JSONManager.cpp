#include "ivypch.h"
#include "JSONManager.h"

#include <json.hpp>
#include <fstream>
#include <iostream>

#include "ECS.h"
#include "../Core/Logger.h"

using Json = nlohmann::json;
namespace Ivy {

	void JSONManager::SaveEntities(const std::string& path) {
		Json jsonNull;
		Json finalObject;

		std::ofstream writer(path);

		for (Entity& entity : ECS::getInstance().getEntities()) {
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

			IVY_CORE_INFO("Read Json Entity {0}", entity);
			IVY_CORE_INFO("Json Object={0}", jsonObject);

			//writer << jsonObject << std::endl;
			//std::cout << std::setw(4) << jsonObject;

			finalObject[entity] = jsonObject;
		}
		writer << std::setw(2) << finalObject << std::endl;

		writer.close();
	}

	void JSONManager::LoadEntities(const std::string& path) {
		std::ifstream reader(path);
		Json json;
		reader >> json;
		reader.close();
		
		for (auto& it = json.begin(); it != json.end(); ++it)
		{
			std::cout << *it << std::endl;
			auto& current = *it;

			Entity entity = ECS::getInstance().createEntity();
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
				ECS::getInstance().addComponent<ScriptComponent>(entity, script);
			}

		}
	}

}