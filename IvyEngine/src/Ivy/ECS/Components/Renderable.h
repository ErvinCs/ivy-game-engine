#pragma once

#include <string>
#include "../Component.h"

namespace Ivy
{
	struct Renderable : public Component
	{
	public:
		std::string spritePath;
	};
}