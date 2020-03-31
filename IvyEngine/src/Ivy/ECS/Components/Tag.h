#pragma once

#include <string>

#include "../Component.h"

namespace Ivy {

	class Tag : public Component
	{
	public:
		std::string tag = "";

		Tag() : Component() {}
		Tag(std::string newTag)
		{
			this->tag = newTag;
			this->setComponentId(3);
		}
	};

}