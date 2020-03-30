#pragma once

#include <set>
#include <queue>
#include <vector>
#include "Entity.h"

namespace Ivy {

	class System
	{
	protected:
		std::vector<Entity>* entities;
	public:
		inline const std::vector<Entity>& getEntities() const { return *entities; }
		inline void setEntities(std::vector<Entity>& inEntities) {  entities = &inEntities; }

		virtual void init() = 0;
		virtual void update(float deltatime) = 0;
	};


}