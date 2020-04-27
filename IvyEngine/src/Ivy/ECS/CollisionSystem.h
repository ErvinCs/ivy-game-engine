#pragma once

#include <stdint.h>
#include <glm/glm.hpp>

#pragma once

#include "System.h"

namespace Ivy {

	class CollisionSystem : public System
	{
	private:
		float maxDistA;
		float maxDistB;
	public:
		CollisionSystem() = default;
		CollisionSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}

		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}