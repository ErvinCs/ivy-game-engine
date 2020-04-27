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
}