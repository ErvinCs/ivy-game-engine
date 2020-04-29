#include "ivypch.h"
#include "Collidable.h"

#include "../ECS.h"

namespace Ivy {

	CollidableBox::CollidableBox(glm::vec2 position, float rotation, glm::vec2 scale)
	{
		//We only ned the half-width & half-height of the scale to compute collision
		this->halfScale = scale;
		this->centerPosition = position;
		this->rotation = rotation;
		this->isTrigger = false;

		//unitX.x = 1.0f * glm::cos(rotation) - 0.0f * glm::sin(rotation);
		//unitX.y = 1.0f * glm::sin(rotation) + 0.0f * glm::cos(rotation);
		this->unitX = glm::vec2(glm::cos(rotation), glm::sin(rotation));
		
		//unitY.x = 0.0f * glm::cos(rotation) - 1.0f * glm::sin(rotation);
		//unitY.y = 0.0f * glm::sin(rotation) + 1.0f * glm::cos(rotation);
		this->unitY = glm::vec2(-glm::sin(rotation), glm::cos(rotation));
		
		this->isCollidingWith = std::unordered_set<Entity>();

		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(CollidableBox).name())->second);
	}

	CollidableBox& CollidableBox::operator=(const CollidableBox& other)
	{
		this->centerPosition = other.centerPosition;
		this->halfScale = other.halfScale;
		this->rotation = other.rotation;
		this->isTrigger = other.isTrigger;
		this->unitX = other.unitX;
		this->unitY = other.unitY;
		if (other.isCollidingWith.size() > 0)
		{
			for (Entity entity : other.isCollidingWith)
			{
				this->isCollidingWith.insert(entity);
			}
		}
		

		return *this;
	}
}