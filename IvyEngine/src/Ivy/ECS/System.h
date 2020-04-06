#pragma once

#include "Entity.h"
#include "EntityContainer.h"

namespace Ivy {

	class System
	{
	protected:
		EntityContainer* entities;
	public:
		inline const EntityContainer& getEntities() const { return *entities; }
		inline void setEntities(EntityContainer& inEntities) {  entities = &inEntities; }

		virtual void init() = 0;
		virtual void update(float deltatime) = 0;
	};


}