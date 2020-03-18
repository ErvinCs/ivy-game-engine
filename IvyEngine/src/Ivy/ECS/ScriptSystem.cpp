#include "ivypch.h"
#include "ScriptSystem.h"

#include "ECS.h"
#include "Components/ScriptComponent.h"

namespace Ivy {

	void ScriptSystem::init()
	{

	}

	void ScriptSystem::update(float deltatime)
	{
		//TODO - Get Script Manager
		for (auto& it = entities.begin(); it != entities.end(); it++)
		{
			auto& object = *it;

			auto& scriptComponent = ECS::getInstance().getComponent<ScriptComponent>(object);

			
			//TODO - Execute OnUpdate() for each script
			//TODO - Execute OnMessage() for each script
			//TODO - Execute OnCollide() for each script [Once the Collision System is implemented]

		}
	}

}