#include "ivypch.h"

#include "ScriptComponent.h"
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
			delete scriptableObject;
	}

	ScriptComponent::ScriptComponent(const ScriptComponent& other)
	{
		this->scriptName = other.scriptName;
		this->componentId = other.componentId;
		this->entityId = other.entityId;
		this->scriptableObject = new ScriptableObject(*other.scriptableObject);
		scriptableObject->setOwner(other.entityId);
	}

	ScriptComponent& ScriptComponent::operator=(const ScriptComponent& other)
	{
		this->scriptName = other.scriptName;
		this->componentId = other.componentId;
		this->entityId = other.entityId;
		this->scriptableObject = new ScriptableObject(*other.scriptableObject);
		scriptableObject->setOwner(other.entityId);

		return *this;
	}
}