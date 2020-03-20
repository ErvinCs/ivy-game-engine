#pragma once

#include "../ECS/ECS.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/Renderable.h"

#include "../Core/InputHandler.h"
#include "../Core/Logger.h"

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

	Transform* FindTransform(Entity entity) {
		Transform* t = &ECS::getInstance().getComponent<Transform>(entity);
		IVY_CORE_TRACE("Entity={0}, Transf.X={1}, Transf.Y={2}", entity, t->positionX, t->positionY);
		return t;
	}

	void GetRenderable(Entity entity, Renderable& renderable)
	{
		renderable = ECS::getInstance().getComponent<Renderable>(entity);
	}

	void GetScriptComponent(Entity entity, ScriptComponent& script)
	{
		script = ECS::getInstance().getComponent<ScriptComponent>(entity);
	}
}