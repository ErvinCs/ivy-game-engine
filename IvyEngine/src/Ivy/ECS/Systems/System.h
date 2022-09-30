#pragma once

#include "../Entity.h"
#include "../EntityContainer.h"

namespace Ivy {
	/**
	 * Base class for Systems.
	 * Children are required to implement `void init()` and `void update(float)`.
	 */
	class System
	{
	protected:
		// Points to the EntityContainer maintained by the ECS
		EntityContainer* entities = nullptr;
	public:
		/**
		 * @return EntityContainer The container maintained by the ECS
		 */
		inline const EntityContainer& getEntities() const { return *entities; }

		/**
		 * Set System to point to an `EntityContainer`
		 * @param inEntites The `EntityContainer` to point to
		 */
		inline void setEntities(EntityContainer& inEntities) {  entities = &inEntities; }

		// Defines system initialization
		virtual void init() = 0;
		// Defines system actions on each frame
		virtual void update(float deltatime) = 0;
	};
}