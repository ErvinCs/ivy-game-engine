#include "ivypch.h"

#include "ScriptComponent.h"
#include "../ECS.h"

namespace Ivy
{
	ScriptComponent::ScriptComponent(std::string scriptName)
	{
		this->scriptName = scriptName;
		this->scriptableObject.setName(scriptName);
		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(ScriptComponent).name())->second);
	}
}