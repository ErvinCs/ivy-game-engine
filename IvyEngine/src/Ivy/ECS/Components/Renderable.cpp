#include "ivypch.h"

#include "Renderable.h"
#include "../ECS.h"

namespace Ivy
{
	Renderable::Renderable(std::string spritePath)
	{
		this->spritePath = spritePath;
		texture = Texture::Create(spritePath);
		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(Renderable).name())->second);
	}
}