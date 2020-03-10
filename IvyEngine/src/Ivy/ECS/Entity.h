#pragma once

#include <stdint.h>
#include <map>

#include "Component.h"

namespace Ivy
{
	class Entity
	{
	private:
		int MAX_ENTITIES = 5000;
		uint16_t entityId;
		// ComponentID to Component mapping
		std::map<uint8_t, Component*> componentRefs;

	public:
		Entity(uint16_t id) : entityId(id) {}

		inline uint16_t getEntityId() {
			return entityId;
		}

		inline void addComponent(Component* component) {
			componentRefs.insert(std::pair<uint16_t, Component*>(component->getComponentId(), component));
		}

		inline void removeComponent(Component* component) {
			componentRefs.erase(component->getComponentId());
		}
	};
}