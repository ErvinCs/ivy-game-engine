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
			this->setComponentId(2);
		}
		
		//~ScriptComponent() {
			// ScriptableObject manages its lifetime
			//delete scriptableObject
			//scriptableObject = nullptr;
		//}
	};
}