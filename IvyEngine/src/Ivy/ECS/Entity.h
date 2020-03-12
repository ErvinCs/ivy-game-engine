#pragma once

#include <stdint.h>
#include <map>

#include "Component.h"

namespace Ivy {

	class Entity
	{
	private:
		uint16_t entityId;
		std::map<uint8_t, std::shared_ptr<Component>> componentRefs; // ComponentID to Component mapping

	public:
		Entity(uint16_t id) : entityId(id) {}

		inline uint16_t getEntityId() {
			return entityId;
		}

		inline void addComponent(const std::shared_ptr<Component>& component) {
			componentRefs.insert(std::pair<uint16_t, std::shared_ptr<Component>>(component->getComponentId(), component));
		}

		inline void removeComponent(const std::shared_ptr<Component>& component) {
			componentRefs.erase(component->getComponentId());
		}
	};
}