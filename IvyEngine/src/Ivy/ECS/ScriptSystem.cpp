#include "ivypch.h"
#include "ScriptSystem.h"

#include "ECS.h"
#include "Components/ScriptComponent.h"

#include "../Scripting/ScriptManager.h"

namespace Ivy {

	void ScriptSystem::init()
	{
		for (auto& it = entities.begin(); it != entities.end(); it++)
		{
			auto& object = *it;
			
			auto& scriptComponent = ECS::getInstance().getComponent<ScriptComponent>(object);
			if (scriptComponent.getComponentId() != uint8_t(2))
				continue;
			scriptComponent.setEntityId(object);

			ScriptManager::GetInstance().createScriptController(scriptComponent.scriptName, scriptComponent.scriptableObject, object);
		}
	}

	void ScriptSystem::update(float deltatime)
	{
		for (auto& it = entities.begin(); it != entities.end(); it++)
		{
			auto& object = *it;

			auto& scriptComponent = ECS::getInstance().getComponent<ScriptComponent>(object);
			if (scriptComponent.getComponentId() != uint8_t(2))
				continue;

			scriptComponent.scriptableObject->onUpdate();
			
			//TODO - Execute onCollide() for each script [Once the Collision System is implemented] - 
		}
	}

}