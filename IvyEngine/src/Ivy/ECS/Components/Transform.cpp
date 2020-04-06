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
}