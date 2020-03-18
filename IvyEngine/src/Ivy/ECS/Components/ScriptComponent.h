#pragma once

#include <string>
#include "../Component.h"

namespace Ivy
{
	struct ScriptComponent : public Component
	{
	public:
		std::string scriptPath;

		ScriptComponent() = default;
		ScriptComponent(std::string scriptPath)
		{
			this->scriptPath = scriptPath;
			this->setComponentId(2);	//TODO - Remove hard-coded set id
		}
	};
}