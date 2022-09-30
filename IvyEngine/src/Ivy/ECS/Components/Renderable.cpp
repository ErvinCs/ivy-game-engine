#include "ivypch.h"

#include "Renderable.h"
#include "../ECS.h"

namespace Ivy {
	Renderable::Renderable(std::string spritePath)
	{
		this->spritePath = spritePath;
		texture = Texture::Create(spritePath);
		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(Renderable).name())->second);
	}

	Renderable::Renderable(const Renderable& other)
	{
		this->spritePath = std::string(other.spritePath);
		this->entityId = other.entityId;
		this->componentId = other.componentId;
		texture = Texture::Create(spritePath);
	}

	Renderable& Renderable::operator=(const Renderable& other)
	{
		this->spritePath = std::string(other.spritePath);
		this->entityId = other.entityId;
		this->componentId = other.componentId;
		texture = Texture::Create(spritePath);

		return *this;
	}
}