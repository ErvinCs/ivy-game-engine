#pragma once

#include "../ECS/ECS.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/Renderable.h"

#include "../Core/InputHandler.h"

namespace Ivy {

	bool IsKeyDown(unsigned int keycode)
	{
		return InputHandler::GetInstance()->IsKeyDown(keycode);
	}

	bool IsMouseButtonDown(unsigned int button)
	{
		return InputHandler::GetInstance()->IsMouseButtonDown(button);
	}


	float GetMouseX()
	{
		return InputHandler::GetInstance()->GetMouseX();
	}

	float GetMouseY()
	{
		return InputHandler::GetInstance()->GetMouseY();
	}

	void GetTransform(Entity entity, Transform& transform)
	{
		transform = ECS::getInstance().getComponent<Transform>(entity);
	}

	void GetRenderable(Entity entity, Renderable& renderable)
	{
		renderable = ECS::getInstance().getComponent<Renderable>(entity);
	}

	void GetScriptComponent(Entity entity, ScriptComponent& script)
	{
		script = ECS::getInstance().getComponent<ScriptComponent>(entity);
	}

	void aaa(Transform& transform)
	{

	}
}