#include "ivypch.h"
#include "TileLocation.h"

#include "../ECS.h"

namespace Ivy
{
	TileLocation::TileLocation(float tileIndexX, float tileIndexY, glm::vec2 previousPosition, Entity owner)
	{
		this->owner = owner;
		this->tileIndexX = tileIndexX;
		this->tileIndexY = tileIndexY;
		this->previousPosition = previousPosition;
		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(TileLocation).name())->second);
	}

	bool TileLocation::operator==(const TileLocation& other)
	{
		return (this->owner == other.owner);
	}
	bool TileLocation::operator!=(const TileLocation& other)
	{
		return (!(*this == other));
	}
}