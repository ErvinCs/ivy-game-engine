#include "ivypch.h"

#include "Transform.h"
#include "../ECS.h"
namespace Ivy
{
	Transform::Transform(glm::vec2 position, float rotation, glm::vec2 scale)
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(Transform).name())->second);
	}

	Transform::Transform(const Transform& other)
	{
		this->position = glm::vec2(other.position);
		this->rotation = other.rotation;
		this->scale = glm::vec2(other.scale);
		this->entityId = other.entityId;
		this->componentId = other.componentId;

	}

	bool Transform::operator==(const Transform& other)
	{
		return this->position == other.position;
	}
	bool Transform::operator!=(const Transform& other)
	{
		return !(*this == other);
	}

	Transform& Transform::operator=(const Transform& other)
	{
		this->position = glm::vec2(other.position);
		this->rotation = other.rotation;
		this->scale = glm::vec2(other.scale);
		this->entityId = other.entityId;
		this->componentId = other.componentId;

		return *this;
	}
}