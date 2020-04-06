#pragma once

#include <string>

#include "../Component.h"

namespace Ivy 
{

	class Tag : public Component
	{
	public:
		std::string tag = "";

		Tag() : Component() {}
		Tag(std::string newTag);
		

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }
	};

}