#include "ivypch.h"
#include "Tag.h"

#include "../ECS.h"

namespace Ivy
{
	Tag::Tag(std::string newTag)
	{
		this->tag = newTag;
		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(Tag).name())->second);
	}

	Tag& Tag::operator=(const Tag& other)
	{
		this->tag = other.tag;
		this->entityId = other.entityId;
		this->componentId = other.componentId;

		return *this;
	}
}