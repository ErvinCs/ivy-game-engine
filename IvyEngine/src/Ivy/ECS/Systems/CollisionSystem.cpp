#include "ivypch.h"
#include "CollisionSystem.h"

#include "../../Core/Logger.h"
#include "../ECS.h"
#include "../Component.h"
#include "../Components/Collidable.h"

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>

namespace Ivy
{
	std::map<Entity, std::vector<Entity>> CollisionSystem::isCollidingWith;

	void CollisionSystem::init()
	{
		for (Entity i = 0; i < MAX_Entities; i++)
		{
			Entity entity = i;
			std::vector<Entity> entityVector{};
			std::pair<Entity, std::vector<Entity>> pair = std::make_pair(entity, entityVector);
			isCollidingWith.insert(pair);
		}
	}

	void CollisionSystem::refresh()
	{
		for (std::pair<const Entity, std::vector<Entity>>& pair : CollisionSystem::isCollidingWith)
		{
			isCollidingWith[pair.first].clear();
		}
	}

	void CollisionSystem::update(float deltatime)
	{
		/*
		J. Huynh - Separating Axis Theorem for Oriented Bounding Boxes
		PA = coordinate position of the center of rectangle A		   - centerPosition
		Ax = unit vector representing the local x-axis of A		       - unitX
		Ay = unit vector representing the local y-axis of A            - unitY
		WA = half width of A (corresponds with the local x-axis of A)  - halfScale.x
		HA = half height of A (corresponds with the local y-axis of A) - halfScale.y
		*/

		for (auto& it = entities->begin(); it != entities->end(); it++)
		{
			auto& object = *it;

			auto& ATransform = ECS::getInstance().getComponent<Transform>(object);
			if (ATransform.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(Transform).name())->second)
				continue;

			auto& A = ECS::getInstance().getComponent<CollidableBox>(object);
			if (A.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(CollidableBox).name())->second)
				continue;

			// Cache the old position of the transform in case it needs to be set back on collision
			glm::vec2 oldPosition = (A.centerPosition);
			A.centerPosition = ATransform.position;

			// For now I've decided to also update the rotation and scale of a Collidable when changing the transform
			// If support for gizmos will be added in the feature, then I'll consider removing it
			// For now there isn't really a use-case for a collidable with different properties than the transform
			A.halfScale = ATransform.scale / 2.0f;
			A.rotation = ATransform.rotation;

			std::vector<Entity>* entityIsColliding = &isCollidingWith[object];
			for (auto& itOther = entities->begin(); itOther != entities->end(); itOther++)
			{
				if (*it == *itOther)
					continue;

				auto& otherObject = *itOther;

				auto& B = ECS::getInstance().getComponent<CollidableBox>(otherObject);
				if (B.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(CollidableBox).name())->second)
					continue;

				// Distance between the object centers
				glm::vec2 T = A.centerPosition - B.centerPosition;

				// Check if the objects are close to eachother and ignore other computations otherwise
				maxDistA = A.halfScale.x > A.halfScale.y ? A.halfScale.x + 0.05f : A.halfScale.y + 0.05f;
				maxDistB = B.halfScale.x > B.halfScale.y ? B.halfScale.x + 0.05f : B.halfScale.y + 0.05f;

				if (glm::length(T) > maxDistA + maxDistB)
				{
					if (entityIsColliding->size() != 0)
					{
						std::vector<Entity>::iterator areColliding = std::find(entityIsColliding->begin(), entityIsColliding->end(), otherObject);
						if (areColliding != entityIsColliding->end())
						{
							entityIsColliding->erase(areColliding);
							//isCollidingWith[otherObject].erase(std::find(isCollidingWith[otherObject].begin(), isCollidingWith[otherObject].end(), object));
						}
					}
					continue;
				}

				// Rectangles A and B collide iff and only if the 4 cases bellow are all false
				if (glm::abs(glm::dot(T, A.unitX)) > A.halfScale.x + glm::abs(glm::dot(B.halfScale.x * B.unitX, A.unitX)) +
					glm::abs(glm::dot(B.halfScale.y * B.unitY, A.unitX)) ||
					glm::abs(glm::dot(T, A.unitY)) > A.halfScale.y + glm::abs(glm::dot(B.halfScale.x * B.unitX, A.unitY)) +
					glm::abs(glm::dot(B.halfScale.y * B.unitY, A.unitY)) ||
					glm::abs(glm::dot(T, B.unitX)) > B.halfScale.x + glm::abs(glm::dot(A.halfScale.x * A.unitX, B.unitX)) +
					glm::abs(glm::dot(A.halfScale.y * A.unitY, B.unitX)) ||
					glm::abs(glm::dot(T, B.unitY)) > B.halfScale.y + glm::abs(glm::dot(A.halfScale.x * A.unitX, B.unitY)) +
					glm::abs(glm::dot(A.halfScale.y * A.unitY, B.unitY)))
				{
					if (entityIsColliding->size() != 0)
					{
						std::vector<Entity>::iterator areColliding = std::find(entityIsColliding->begin(), entityIsColliding->end(), otherObject);
						if (areColliding != entityIsColliding->end())
						{
							entityIsColliding->erase(areColliding);
							//isCollidingWith[otherObject].erase(std::find(isCollidingWith[otherObject].begin(), isCollidingWith[otherObject].end(), object));
						}		
					}
					continue;	
				}

				entityIsColliding->push_back(otherObject);
				//isCollidingWith[otherObject].push_back(object);


				if (A.isTrigger || B.isTrigger)
				{
					//IVY_CORE_TRACE("CollisionSystem: Trigger: Entity {0} with Entity {1}", object, otherObject);
				}
				else
				{
					//IVY_CORE_TRACE("CollisionSystem: Collider: Entity {0} with Entity {1}", object, otherObject);
					A.centerPosition = oldPosition;
					ATransform.position = oldPosition;
				}
			}
		}

	}
}