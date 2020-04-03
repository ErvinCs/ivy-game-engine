#include "ivypch.h"
#include "ScriptSystem.h"

#include "ECS.h"
#include "Components/ScriptComponent.h"

#include "../Scripting/ScriptManager.h"
#include "../Core/ResourcePaths.h"

namespace Ivy {

	void ScriptSystem::init()
	{
		for (auto& it = entities->begin(); it != entities->end(); it++)
		{
			auto& object = *it;
			
			auto& scriptComponent = ECS::getInstance().getComponent<ScriptComponent>(object);
			if (scriptComponent.getComponentId() != uint8_t(2))
				continue;
			scriptComponent.setEntityId(object);

			ScriptManager::GetInstance().createScriptController((Paths::scriptsPath / scriptComponent.scriptName).string(), &scriptComponent.scriptableObject, object);
			IVY_CORE_INFO("ScriptSystem: Creating ScriptController: {0}, Path={1}", scriptComponent.scriptName, scriptComponent.scriptableObject.getName());
		}
	}

	void ScriptSystem::update(float deltatime)
	{
		for (auto& it = entities->begin(); it != entities->end(); it++)
		{
			auto& object = *it;

			auto& scriptComponent = ECS::getInstance().getComponent<ScriptComponent>(object);
			if (scriptComponent.getComponentId() != uint8_t(2))
				continue;

			//IVY_CORE_INFO("ScriptSystem: Updating ScriptController: {0}, Path={1}", scriptComponent.scriptName, scriptComponent.scriptableObject.getName());
			scriptComponent.scriptableObject.onUpdate();
			
			//TODO - Execute onCollide() for each script [Once the Collision System is implemented] - 
		}
	}

}