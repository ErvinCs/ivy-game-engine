#pragma once

#include <set>
#include <queue>
#include <vector>
#include "Entity.h"

namespace Ivy {

	class System
	{
	protected:
		std::vector<Entity> entities;
	public:
		inline const std::vector<Entity>& getEntities() const { return entities; }
		inline void setEntities(const std::vector<Entity>& entities) { this->entities = entities; }

		virtual void init() = 0;
		virtual void update(float deltatime) = 0;
	};


}