#include "ivypch.h"
#include "CollisionSystem.h"

#include "../Core/Logger.h"

#include "ECS.h"
#include "Component.h"
#include "Components/Collidable.h"

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>

namespace Ivy
{
	void CollisionSystem::init()
	{

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

			auto& A = ECS::getInstance().getComponent<Collidable>(object);
			if (A.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(Collidable).name())->second)
				continue;

			// Cache the old position of the transform in case it needs to be set back on collision
			glm::vec2 oldPosition = (A.centerPosition);
			A.centerPosition = ATransform.position;

			// For now I've decided to also update the rotation and scale of a Collidable when changing the transform
			// If support for gizmos will be added in the feature, then I'll consider removing this segment
			// For now there isn't really a use-case for a collidable with different properties than the transform
			//TODO update scale ?
			//TODO update rotation ? 

			for (auto& itOther = entities->begin(); itOther != entities->end(); itOther++)
			{
				if (*it == *itOther)
					continue;
				
				auto& otherObject = *itOther;

				auto& B = ECS::getInstance().getComponent<Collidable>(otherObject);
				if (B.getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(Collidable).name())->second)
					continue;

				glm::vec2 T = A.centerPosition - B.centerPosition;			
				// Rectangles A and B collide iff and only if the 4 cases bellow are all false
				if (glm::abs(glm::dot(T, A.unitX)) > A.halfScale.x + glm::abs(glm::dot(B.halfScale.x * B.unitX, A.unitX)) +
					glm::abs(glm::dot(B.halfScale.y * B.unitY, A.unitX)))
					continue;
				if (glm::abs(glm::dot(T, A.unitY)) > A.halfScale.y + glm::abs(glm::dot(B.halfScale.x * B.unitX, A.unitY)) +
					glm::abs(glm::dot(B.halfScale.y * B.unitY, A.unitY)))
					continue;
				if (glm::abs(glm::dot(T, B.unitX)) > B.halfScale.x + glm::abs(glm::dot(A.halfScale.x * A.unitX, B.unitX)) +
					glm::abs(glm::dot(A.halfScale.y * A.unitY, B.unitX)))
					continue;
				if (glm::abs(glm::dot(T, B.unitY)) > B.halfScale.y + glm::abs(glm::dot(A.halfScale.x * A.unitX, B.unitY)) +
					glm::abs(glm::dot(A.halfScale.y * A.unitY, B.unitY)))
					continue;

				A.centerPosition = oldPosition;
				IVY_CORE_TRACE("Collided!");
				// Temporary - Should raise event onCollision
				ATransform.position = oldPosition;
			}
		}

	}
}