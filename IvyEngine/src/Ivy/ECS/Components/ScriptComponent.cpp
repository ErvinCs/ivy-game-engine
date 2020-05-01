#include "ivypch.h"

#include "ScriptComponent.h"
#include "../../Scripting/ScriptManager.h"
#include "../ECS.h"

namespace Ivy
{
	ScriptComponent::ScriptComponent(std::string scriptName)
	{
		this->scriptName = scriptName;
		this->scriptableObject = new ScriptableObject(scriptName);
		this->setComponentId(ECS::getInstance().getComponentTypes().find(typeid(ScriptComponent).name())->second);
	}

	ScriptComponent::~ScriptComponent()
	{
		if (scriptableObject != NULL)
		{
			scriptableObject->setAlive(false);
			delete scriptableObject;
			scriptableObject = NULL;
		}
	}

	ScriptComponent::ScriptComponent(const ScriptComponent& other)
	{
		this->scriptName = std::string(other.scriptName);
		this->componentId = other.componentId;
		this->entityId = other.entityId;
		if (other.scriptableObject != NULL)
		{
			this->scriptableObject = new ScriptableObject(*other.scriptableObject);
			scriptableObject->setOwner(other.entityId);
		}
		else
		{
			this->scriptableObject = NULL;
		}
	}

	ScriptComponent& ScriptComponent::operator=(const ScriptComponent& other)
	{
		this->scriptName = std::string(other.scriptName);
		this->componentId = other.componentId;
		this->entityId = other.entityId;
		if (other.scriptableObject != NULL)
		{
			this->scriptableObject = new ScriptableObject(*other.scriptableObject);
			scriptableObject->setOwner(other.entityId);
		}
		else
		{
			this->scriptableObject = NULL;
		}

		return *this;
	}
}