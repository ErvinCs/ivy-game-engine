#pragma once

#include <map>
#include <stdint.h>
#include <glm/glm.hpp>

#include "../Entity.h"
#include "System.h"

namespace Ivy {

	class CollisionSystem : public System
	{
	private:
		float maxDistA;
		float maxDistB;
	public:
		static std::map<Entity, std::vector<Entity>> isCollidingWith;

		CollisionSystem() = default;
		CollisionSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}

		static void refresh();
		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}