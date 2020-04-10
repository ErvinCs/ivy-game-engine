#pragma once

#include "System.h"

namespace Ivy {

	class CollisionSystem : public System
	{
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