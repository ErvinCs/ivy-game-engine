#pragma once

#include <string>
#include "../Component.h"

namespace Ivy
{
	struct Renderable : public Component
	{
	public:
		std::string spritePath;

		Renderable() = default;
		Renderable(std::string spritePath)
		{
			this->spritePath = spritePath;
			this->setComponentId(1);
		}
	};
}