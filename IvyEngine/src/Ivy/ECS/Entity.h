#pragma once

#include <stdint.h>
#include <map>

#include "Component.h"

namespace Ivy {

	class Entity
	{
	private:
		uint16_t entityId;
		//std::map<uint8_t, std::shared_ptr<Component>> componentRefs; // ComponentID to Component mapping
		//std::map<uint8_t, Component*> compRefs;

	public:
		Entity() = default;
		Entity(const uint16_t& id) : entityId(id) {}
		~Entity() = default;
		/*{
			for (auto& pair : compRefs)
			{
				compRefs.erase(pair.second->getComponentId());
				delete pair.second;
			}
		}*/

		inline const uint16_t getEntityId() const {
			return entityId;
		}

		/*inline void addComponent(Component* component) {
			compRefs.insert(std::pair<uint8_t, Component*>(component->getComponentId(), component));
		}

		inline void removeComponent(Component* component) {
			compRefs.erase(component->getComponentId());
			delete component;
		}

		/*inline void addComponent(const std::shared_ptr<Component>& component) {
			componentRefs.insert(std::pair<uint8_t, std::shared_ptr<Component>>(component->getComponentId(), component));
		}

		inline void removeComponent(const std::shared_ptr<Component>& component) {
			componentRefs.erase(component->getComponentId());
		}*/

		// ----- Operators -----

		bool operator==(const Entity& other)
		{
			return this->entityId == other.getEntityId();
		}
		bool operator!=(const Entity& other)
		{
			return !(this->entityId == other.getEntityId());
		}

		bool operator<(const Entity& other)
		{
			return this->entityId < other.getEntityId();
		}

		bool operator>(const Entity& other)
		{
			return this->entityId > other.getEntityId();
		}

		bool operator<=(const Entity& other)
		{
			return this->entityId <= other.getEntityId();
		}

		bool operator>=(const Entity& other)
		{
			return this->entityId >= other.getEntityId();
		}
	};
}