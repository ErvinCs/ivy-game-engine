#pragma once

#include <map>
#include <vector>
#include <stdint.h>
#include <fstream>

#include "EntityContainer.h"
#include "Component.h"
#include "ComponentContainer.h"
#include "Entity.h"
#include "System.h"
#include "Components/Transform.h"
#include "Components/Renderable.h"
#include "Components/ScriptComponent.h"
#include "Components/Tag.h"
#include "Components/Collidable.h"

#include "../Core/ResourcePaths.h"
#include "../Core/Logger.h"
#include "JSONManager.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"
#include "CollisionSystem.h"
#include "CollidableGizmoSystem.h"
#include "CameraSystem.h"

namespace Ivy {

	class ECS
	{
	private:
		uint8_t componentTypeCounter;
		std::map<const char*, std::shared_ptr<BaseComponentContainer>> componentContainers{};
		std::map<const char*, uint8_t> componentTypes{};
		EntityContainer entities;
		std::vector<std::shared_ptr<System>> systems{};
	public:

		~ECS()
		{
			IVY_CORE_INFO("ECS: Clearing entities. Clearing components. Clearing systems.");
			for (auto& it = entities.begin(); it != entities.end(); it++)
			{
				destroyEntity(*it);
			}
			
			componentTypes.clear();
			componentContainers.clear();
			systems.clear();
		}

		static ECS& getInstance()
		{
			static ECS instance{};
			return instance;
		}

		void loadEntities() {
			IVY_CORE_INFO("ECS: Loading Entities from {0}", Paths::entitiesRepoPath.string());
			if (std::filesystem::exists(Paths::entitiesRepoPath)) {
				JSONManager::LoadEntities(Paths::entitiesRepoPath.string());
			}
			else {
				std::ofstream writer(Paths::entitiesRepoPath.string());
				writer.close();
				IVY_CORE_INFO("ECS: Entitiy JSON file was not found. Creating empty entities.json.");
			}
			IVY_CORE_INFO("ECS: Loading camera from {0}", Paths::cameraRepoPath.string());
			if (std::filesystem::exists(Paths::cameraRepoPath)) {
				JSONManager::LoadCamera(Paths::cameraRepoPath.string());
			}
			else {
				std::ofstream writer(Paths::cameraRepoPath.string());
				writer.close();
				IVY_CORE_INFO("ECS: Camera JSON file was not found. Creating empty camera.json.");
			}
		}

		void saveEntities() {
			IVY_CORE_INFO("ECS: Saving Entities to {0}", Paths::entitiesRepoPath.string());
			JSONManager::SaveEntities(Paths::entitiesRepoPath.string());
			IVY_CORE_INFO("ECS: Saving Camera to {0}", Paths::cameraRepoPath.string());
			JSONManager::SaveCamera(Paths::cameraRepoPath.string());
		}

		void clearECS()
		{
			for (auto& componentContainer : componentContainers)
			{
				componentContainer.second->clearComponents();
			}
			this->entities.clearEntities();
		}

		int getSizeEntities() {
			return this->entities.size();
		}

		// Components
		template<typename T>
		uint8_t addComponentType()
		{
			// Log produces error
			//IVY_CORE_INFO("ECS: Registering new Component: type={0}, id={1}", typeid(T).name(), componentTypeCounter);
			const char* typeName = typeid(T).name();

			// Add a new component type
			componentTypes.insert({ typeName, componentTypeCounter });
			// Add a component container for the new type
			componentContainers.insert({ typeName, std::move(std::make_shared<ComponentContainer<T>>()) });

			componentTypeCounter++;
			return componentTypeCounter - 1;
		}

		//TEMPORARY - Until bitset is implemented
		uint8_t generateComponentId()
		{
			return componentTypeCounter;
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
			
			entities.destroyEntity(entity);
		}

		Entity& createEntity()
		{
			return entities.createEntity();
		}

		void addToFreeEntities(Entity entity)
		{
			entities.addToFreeEntities(entity);
		}

		void addToEntities(uint16_t entity)
		{
			entities.addToEntities(entity);
		}

		EntityContainer& getEntities()
		{
			return this->entities;
		}

		// Systems
		void addSystem(const std::shared_ptr<System>& system)
		{
			IVY_CORE_INFO("ECS: Registering System");
			systems.push_back(std::move(system));
		}

		void updateSystems(float ts) {
			for (std::shared_ptr<System> system : systems)
			{
				system->update(ts);
			}
		}

		void initSystems() {
			std::shared_ptr<System> renderSystem    = std::make_shared<RenderSystem>(entities);
			std::shared_ptr<System> scriptSystem    = std::make_shared<ScriptSystem>(entities);
			std::shared_ptr<System> collisionSystem = std::make_shared<CollisionSystem>(entities);
			std::shared_ptr<System> collisionGizmos = std::make_shared<CollidableGizmoSystem>(entities);
			std::shared_ptr<System> cameraSystem    = std::make_shared<CameraSystem>(entities);
			
			renderSystem->init();
			collisionSystem->init();
			collisionGizmos->init();
			scriptSystem->init();
			cameraSystem->init();

			addSystem(renderSystem);
			addSystem(collisionSystem);
			addSystem(collisionGizmos);
			addSystem(scriptSystem);
			addSystem(cameraSystem);
		}


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
			componentTypeCounter = 1;

			// Component Types
			this->registerComponentTypes();
		}

		void registerComponentTypes() {
			//IVY_CORE_INFO("ECS: Registering Ivy Component Types");
			this->addComponentType<Transform>();		
			this->addComponentType<Renderable>();		
			this->addComponentType<ScriptComponent>();	
			this->addComponentType<Tag>();	
			this->addComponentType<CollidableBox>();
		}

		ECS(const ECS&) = delete;
		ECS& operator=(const ECS&) = delete;
	public:

	};
}