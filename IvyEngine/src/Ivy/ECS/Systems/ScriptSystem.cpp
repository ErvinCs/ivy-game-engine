#include "ivypch.h"
#include "ScriptSystem.h"

#include "../ECS.h"
#include "../Components/ScriptComponent.h"

#include "../../Scripting/ScriptManager.h"
#include "../../Core/ResourcePaths.h"

namespace Ivy {

	void ScriptSystem::init()
	{
		IVY_CORE_INFO("ScriptSystem: Initializing System");
		for (auto& it = entities->begin(); it != entities->end(); it++)
		{
			auto& object = *it;
			
			ScriptComponent* scriptComponent = &ECS::getInstance().getComponent<ScriptComponent>(object);
			if (scriptComponent->getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(ScriptComponent).name())->second)
				continue;
			scriptComponent->setEntityId(object);

			ScriptManager::GetInstance().createScriptController((Paths::scriptsPath / scriptComponent->scriptName).string(), scriptComponent->scriptableObject, object);
			IVY_CORE_INFO("ScriptSystem: Creating ScriptController: scriptName={0}, path={1}", scriptComponent->scriptName, scriptComponent->scriptableObject->getName());
		}
	}

	void ScriptSystem::update(float deltatime)
	{
		int size = entities->size();
		for (int i = 0; i < size; i++)
		{
			ScriptComponent* scriptComponent = &ECS::getInstance().getComponent<ScriptComponent>(*entities->at(i));
			if (scriptComponent->getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(ScriptComponent).name())->second)
				continue;

			if (!scriptComponent->scriptableObject->isAlive())
			{
				delete scriptComponent->scriptableObject;
				scriptComponent->scriptableObject = NULL;
				ECS::getInstance().removeComponent<ScriptComponent>(entities->getEntity(*entities->at(i)));
				i--;
				size--;
				continue;
			}

			scriptComponent->scriptableObject->onUpdate();
		}
	}

}