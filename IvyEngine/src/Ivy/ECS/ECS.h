#pragma once

#include <map>
#include <vector>
#include <stdint.h>
#include <filesystem>

#include "Component.h"
#include "ComponentContainer.h"
#include "Entity.h"
#include "System.h"
#include "Components/Transform.h"
#include "Components/Renderable.h"
#include "Components/ScriptComponent.h"
#include "Components/Tag.h"

#include "../Core/Logger.h"
#include "JSONManager.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"

namespace Ivy {

	class ECS
	{
	private:
		uint16_t EntityIdGenerator;
		uint8_t componentTypeCounter;
		std::map<const char*, std::shared_ptr<BaseComponentContainer>> componentContainers{};
		std::map<const char*, uint8_t> componentTypes{};
		std::vector<Entity> entities{};
		std::vector<std::shared_ptr<System>> systems{};
	public:
		const char* entitiesRepoPath = "C:\\Workspace\\ivy-game-engine\\IvyApplication\\res\\entities.json";
		~ECS()
		{
			for (auto& it = entities.begin(); it != entities.end(); it++)
			{
				destroyEntity(*it);
			}
			componentTypes.clear();
			componentContainers.clear();
			systems.clear();
			entities.clear();
		}

		static ECS& getInstance()
		{
			static ECS instance{};
			return instance;
		}

		void loadEntities() {
			if (std::filesystem::exists(entitiesRepoPath))
				JSONManager::LoadEntities(entitiesRepoPath);
			else
				IVY_CORE_WARN("Entity JSON repository not found!");
		}

		void saveEntities() {
			JSONManager::SaveEntities(entitiesRepoPath);
		}

		// Components
		template<typename T>
		void addComponentType()
		{
			const char* typeName = typeid(T).name();

			// Add a new component type
			componentTypes.insert({ typeName, componentTypeCounter });
			// Add a component container for the new type
			componentContainers.insert({ typeName, std::move(std::make_shared<ComponentContainer<T>>()) });

			componentTypeCounter++;
		}

		const std::map<const char*, uint8_t>& getComponentTypes() {
			return this->componentTypes;
		}

		template<typename T>
		void addComponent(Entity& entity, T component)
		{
			getComponentContainer<T>()->addComponent(entity, component);
		}

		template<typename T>
		void removeComponent(Entity& entity)
		{
			getComponentContainer<T>()->removeComponent(entity);
		}

		template<typename T>
		T& getComponent(Entity& entity)
		{
			return getComponentContainer<T>()->getComponent(entity);
		}



		// Entities
		void destroyEntity(Entity& entity)
		{
			for (auto const& containerPair : componentContainers)
			{
				auto const& container = containerPair.second;

				container->onEntityDestroyed(entity);
			}
			
			for (auto& it = entities.begin(); it != entities.end(); it++)
			{
				if(*it == entity)
				{
					entities.erase(it);
					break;
				}
			}
		}

		Entity& createEntity()
		{
			Entity entity = EntityIdGenerator; 
			entities.push_back(entity);
			EntityIdGenerator++;
			return entities.at(entities.size() - 1);
		}

		std::vector<Entity>& getEntities() {
			return this->entities;
		}

		// Systems
		void addSystem(const std::shared_ptr<System>& system)
		{
			systems.push_back(std::move(system));
		}

		/*void updateSystems(float ts) {
			for (std::shared_ptr<System> system : systems)
			{
				system->update(ts);
			}
		}

		void initSystems() {
			std::shared_ptr<Ivy::System> renderSystem = std::make_shared<RenderSystem>(entities);
			std::shared_ptr<Ivy::System> scriptSystem = std::make_shared<ScriptSystem>(entities);
			systems.push_back(renderSystem);
			systems.push_back(scriptSystem);
		}*/


	private:
		template<typename T>
		std::shared_ptr<ComponentContainer<T>> getComponentContainer()
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<ComponentContainer<T>>(componentContainers[typeName]);
		}	

		ECS()
		{
			// Ids
			EntityIdGenerator = 0;
			componentTypeCounter = 0;

			// Component Types
			this->registerComponentTypes();
			

			// Init systems
			//this->initSystems();
		}

		void registerComponentTypes() {
			this->addComponentType<Transform>();		//TransformID       = 0
			this->addComponentType<Renderable>();		//RenderableID      = 1
			this->addComponentType<ScriptComponent>();	//ScriptComponentID = 2	
			this->addComponentType<Tag>();				//TagID				= 3
		}

		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;
	};
}