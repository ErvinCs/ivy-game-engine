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
		ScriptableObject* scriptableObject;

		ScriptComponent() : Component() 
		{
			this->scriptName = "";
			this->scriptableObject = new ScriptableObject();
		}
		ScriptComponent(std::string scriptName);
		ScriptComponent(const ScriptComponent& other);
		~ScriptComponent();

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		ScriptComponent& operator=(const ScriptComponent& other);
	};
}