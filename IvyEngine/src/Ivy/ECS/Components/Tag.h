#pragma once

#include <string>

#include "../Component.h"

namespace Ivy 
{

	struct Tag : public Component
	{
	public:
		std::string tag = "";

		Tag() : Component() {}
		Tag(std::string newTag);
		Tag(const Tag& other);

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		Tag& operator=(const Tag& other);
	};

}