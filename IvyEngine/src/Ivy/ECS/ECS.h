#pragma once

#include <map>
#include <vector>
#include <stdint.h>
#include <fstream>

#include "EntityContainer.h"
#include "Component.h"
#include "ComponentContainer.h"
#include "Entity.h"
#include "Systems/System.h"
#include "Components/Transform.h"
#include "Components/Renderable.h"
#include "Components/ScriptComponent.h"
#include "Components/Tag.h"
#include "Components/Collidable.h"
#include "Components/TileLocation.h"

#include "../Core/ResourcePaths.h"
#include "../Core/Logger.h"
#include "JSONManager.h"
#include "Systems/RenderSystem.h"
#include "Systems/ScriptSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/CollidableGizmoSystem.h"
#include "Systems/CameraSystem.h"

namespace Ivy {
	/**
	 * The singleton ECS class is in charge of managing Entities, Components and Systems.
	 * It provides functionality to add or remove Entities or attach or detach components to them.
	 * It also runs the systems, calling their `init` and `update` functions. The Systems operate on 
	 *  the components that share the same aspect as them.
	 * @see Entity
	 * @see Component
	 * @see System
	 */
	class ECS
	{
	private:
		uint8_t componentTypeCounter;
		std::map<const char*, std::shared_ptr<BaseComponentContainer>> componentContainers{};
		std::map<const char*, uint8_t> componentTypes{};
		EntityContainer entities;
		std::vector<std::shared_ptr<System>> systems{};
	public:
		/**
		 * Clears all component types and component containers
		 * Clears all systems.
		 */
		~ECS()
		{	
			componentTypes.clear();
			componentContainers.clear();
			systems.clear();
		}
		/**
		 * @return ECS& Singleton instance of this class
		 */
		static ECS& getInstance()
		{
			static ECS instance{};
			return instance;
		}

		/**
		 * Loads the camera.
		 * Loads all the entities and their components.
		 * They are loaded from the JSON files in the `res` folder.
		 */
		void loadEntities() {
			IVY_CORE_INFO("ECS: Loading Entities from {0}", Paths::ENTITIES_REPO_PATH.string());
			if (std::filesystem::exists(Paths::ENTITIES_REPO_PATH)) {
				JSONManager::LoadEntities(Paths::ENTITIES_REPO_PATH.string());
			}
			else {
				std::ofstream writer(Paths::ENTITIES_REPO_PATH.string());
				writer.close();
				IVY_CORE_INFO("ECS: Entitiy JSON file was not found. Creating empty entities.json.");
			}
			IVY_CORE_INFO("ECS: Loading camera from {0}", Paths::CAMERA_REPOSITORY_PATH.string());
			if (std::filesystem::exists(Paths::CAMERA_REPOSITORY_PATH)) {
				JSONManager::LoadCamera(Paths::CAMERA_REPOSITORY_PATH.string());
			}
			else {
				std::ofstream writer(Paths::CAMERA_REPOSITORY_PATH.string());
				writer.close();
				IVY_CORE_INFO("ECS: Camera JSON file was not found. Creating empty camera.json.");
			}
		}

		/**
		 * Saves the camera properties.
		 * Saves the entities and their components.
		 * They are saved into the JSON files in the `res` folder.
		 */
		void saveEntities() {
			IVY_CORE_INFO("ECS: Saving Entities to {0}", Paths::ENTITIES_REPO_PATH.string());
			JSONManager::SaveEntities(Paths::ENTITIES_REPO_PATH.string());
			IVY_CORE_INFO("ECS: Saving Camera to {0}", Paths::CAMERA_REPOSITORY_PATH.string());
			JSONManager::SaveCamera(Paths::CAMERA_REPOSITORY_PATH.string());
		}

		/**
		 * Clear all components and entities.
		 */
		void clearECS()
		{
			for (auto& componentContainer : componentContainers)
			{
				componentContainer.second->clearComponents();
			}
			this->entities.clearEntities();
		}

		/**
		 * @return int the number of live entities
		 */
		int getSizeEntities() {
			return this->entities.size();
		}

		// ---------- Components ----------

		/**
		 * Register a new component type with the engine.
		 * Creates a new component container for the registered type.
		 * @return uint8_t the index in the container of the component type that was added
		 */
		template<typename T>
		uint8_t addComponentType()
		{
			const char* typeName = typeid(T).name();

			// Add a new component type
			componentTypes.insert({ typeName, componentTypeCounter });
			// Add a component container for the new type
			componentContainers.insert({ typeName, std::move(std::make_shared<ComponentContainer<T>>()) });

			componentTypeCounter++;
			return componentTypeCounter - 1;
		}

		/**
		 * @return uint8_t a component ID
		 */
		uint8_t generateComponentId()
		{
			return componentTypeCounter;
		}

		/**
		 * @return map<const char*, uint8_t>& a reference to the map holding the registered component types <name, identifier>
		 */
		const std::map<const char*, uint8_t>& getComponentTypes() {
			return this->componentTypes;
		}

		/**
		 * Associate a component of type T to an Entity
		 * @param entity Entity to add the component to
		 * @param component T
		 */
		template<typename T>
		void addComponent(Entity& entity, T component)
		{
			getComponentContainer<T>()->addComponent(entity, component);
		}

		/**
		 * Remove a component of type T from an Entity.
		 * @param entity Entity to remove the component from
		 */
		template<typename T>
		void removeComponent(Entity& entity)
		{
			getComponentContainer<T>()->removeComponent(entity);
		}

		/**
		 * Get the component of type T from an Entity
		 * @param entity Entity to query
		 * @returns T& the component
		 */
		template<typename T>
		T& getComponent(Entity& entity)
		{
			return getComponentContainer<T>()->getComponent(entity);
		}



		// ---------- Entities -----------

		/**
		 * Removes `entity` from the `EntityContainer` and destorys all of its associated components
		 *  in their respective `ComponentContainer`s.
		 * @param entity Entity to destroy
		 */
		void destroyEntity(Entity& entity)
		{
			for (auto const& containerPair : componentContainers)
			{
				auto const& container = containerPair.second;

				container->onEntityDestroyed(entity);
			}
			
			entities.destroyEntity(entity);
		}

		/**
		 * @return Entity& a reference to a newly created Entity
		 */
		Entity& createEntity()
		{
			return entities.createEntity();
		}

		/**
		 * Add an Entity to the array of `freeEntities`
		 * @param entity Entity
		 * @see EntityContainer
		 */
		void addToFreeEntities(Entity entity)
		{
			entities.addToFreeEntities(entity);
		}

		/**
		 * Add an Entity to the array of `entities`.
		 * @param entity uint16_t the ID of the entity
		 * @see EntityContainer
		 */
		void addToEntities(uint16_t entity)
		{
			entities.addToEntities(entity);
		}

		/**
		 * @returns EntityContainer&
		 */
		EntityContainer& getEntities()
		{
			return this->entities;
		}

		// ---------- Systems ----------

		/**
		 * Registers a system with the ECS
		 * @param system pointer to the System to be added
		 * @see System
		 */
		void addSystem(const std::shared_ptr<System>& system)
		{
			IVY_CORE_INFO("ECS: Registering System");
			systems.push_back(std::move(system));
		}

		/**
		 * Calls the update method of all Systems
		 * @param ts Timestep to regulate framerate
		 * @see System
		 */
		void updateSystems(float ts) {
			for (std::shared_ptr<System> system : systems)
			{
				system->update(ts);
			}
		}

		/**
		 * Initialize and add to the System container all engine systems.
		 * Note that if NOT running in DEBUG mode then the GizmoSystem is not initialized.
		 */
		void initSystems() {
			std::shared_ptr<System> renderSystem    = std::make_shared<RenderSystem>(entities);
			std::shared_ptr<System> scriptSystem    = std::make_shared<ScriptSystem>(entities);
			std::shared_ptr<System> collisionSystem = std::make_shared<CollisionSystem>(entities);
			std::shared_ptr<System> cameraSystem    = std::make_shared<CameraSystem>(entities);

#ifdef _DEBUG
			std::shared_ptr<System> collisionGizmos = std::make_shared<CollidableGizmoSystem>(entities);
			collisionGizmos->init();
			addSystem(collisionGizmos);
#endif
			renderSystem->init();
			addSystem(renderSystem);

			collisionSystem->init();
			addSystem(collisionSystem);

			scriptSystem->init();
			addSystem(scriptSystem);

			cameraSystem->init();	
			addSystem(cameraSystem);
		}


	private:
		/**
		 * @returns ComponentContainer<T>, where T is the type of Component contained.
		 */
		template<typename T>
		std::shared_ptr<ComponentContainer<T>> getComponentContainer()
		{
			const char* typeName = typeid(T).name();

			return std::static_pointer_cast<ComponentContainer<T>>(componentContainers[typeName]);
		}	

		/**
		 * Initalizes the `componentTypeCounter` and registers all default component types.
		 */
		ECS()
		{
			// Ids
			componentTypeCounter = 1;

			// Component Types
			this->registerComponentTypes();
		}

		/**
		 * Registers all default component types.
		 */
		void registerComponentTypes() {
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