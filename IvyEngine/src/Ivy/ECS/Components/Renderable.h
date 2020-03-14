#pragma once

#include <string>
#include "../Component.h"
#include "../../Renderer/Texture.h"

namespace Ivy
{
	struct Renderable : public Component
	{
	public:
		std::string spritePath;
		std::shared_ptr<Ivy::Texture> texture;

		Renderable() = default;
		Renderable(std::string spritePath)
		{
			this->spritePath = spritePath;
			texture = Texture::Create(spritePath);
			this->setComponentId(1);	//TODO - Remove hard-coded set id
		}
	};
}