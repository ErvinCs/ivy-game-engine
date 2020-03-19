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

		ScriptComponent() : Component() {}
		ScriptComponent(std::string scriptName)
		{
			this->scriptName = scriptName;
			this->scriptableObject = new ScriptableObject(scriptName);
			this->setComponentId(2);	//TODO - Remove hard-coded set id
		}
		~ScriptComponent() {
			delete scriptableObject;
			scriptableObject = nullptr;
		}
	};
}