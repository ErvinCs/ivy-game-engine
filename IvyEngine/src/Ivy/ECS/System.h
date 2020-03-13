#pragma once

#include <set>
#include <queue>
#include <vector>
#include "Entity.h"

namespace Ivy {

	class System
	{
	protected:
		//std::shared_ptr<std::set<Entity>> entities;
		std::vector<Entity> entities;
	public:
		//inline const std::shared_ptr<std::set<Entity>>& getEntities() { return this->entities; }
		//inline void setEntities(const std::shared_ptr<std::set<Entity>>& entities)
		//{
		//	this->entities = entities;
		//}

		inline const std::vector<Entity>& getEntities() const { return entities; }
		inline void setEntities(const std::vector<Entity>& entities) { this->entities = entities; }

		virtual void init() = 0;
		virtual void update(float deltatime) = 0;
	};


}