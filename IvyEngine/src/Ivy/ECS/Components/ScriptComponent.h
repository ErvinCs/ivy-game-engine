#pragma once

#include <string>
#include "../Component.h"
#include "../../Scripting/ScriptableObject.h"

namespace Ivy
{

	struct ScriptComponent : public Component
	{
	public:
		std::string scriptName;
		ScriptableObject scriptableObject;

		ScriptComponent() : Component() {}
		ScriptComponent(std::string scriptName);
		

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }
	};
}