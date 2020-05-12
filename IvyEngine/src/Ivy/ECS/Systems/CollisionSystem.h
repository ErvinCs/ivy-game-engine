#pragma once

#include <map>
#include <stdint.h>
#include <glm/glm.hpp>

#include "../Entity.h"
#include "System.h"

namespace Ivy {

	/**
	 * System used to detect collision between entities.
	 * Requires a CollidableBox and a Transform.
	 * Uses Bounding Circles as a preliminary test
	 * Uses the Separating Axis theorem for Oriented Bounding Boxes.
	 * @see System
	 * @see CollidableBox
	 */
	class CollisionSystem : public System
	{
	private:
		// Cache the longest side of the box for the 1st entity testing for collision
		float maxDistA;
		// Cache the longest side of the box for the 1st entity testing for collision
		float maxDistB;
	public:
		/**
		 * Map used to represent the collision world
		 * For each entity it stores the vector of the entities it is colliding with in a given frame
		 */
		static std::map<Entity, std::vector<Entity>> isCollidingWith;

		CollisionSystem() = default;
		CollisionSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}

		/**
		 * Resets the collision map to its initial state, where no entity is colliding
		 */
		static void refresh();

		/**
		 * Initializes the `isCollidingWith` map.
		 */
		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}