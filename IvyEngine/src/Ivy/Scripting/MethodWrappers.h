#pragma once

#include "../ECS/ECS.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/Renderable.h"

#include "../Core/InputHandler.h"
#include "../Core/Logger.h"

#include "../Core/Timestep.h"

#include <glm/glm.hpp>

namespace Ivy {

	// ---------- Input ----------
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


	// ---------- Find Components ----------
	Transform* FindTransform(Entity entity) {
		Transform* t = &ECS::getInstance().getComponent<Transform>(entity);
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

	// ---------- Timestep ----------

	Timestep operator+(const Timestep& lhs, const Timestep& rhs)
	{
		return lhs.getSeconds() + rhs.getSeconds();
	}

	Timestep operator-(const Timestep& lhs, const Timestep& rhs)
	{
		return lhs.getSeconds() - rhs.getSeconds();
	}

	Timestep operator/(const Timestep& lhs, const Timestep& rhs)
	{
		return lhs.getSeconds() / rhs.getSeconds();
	}

	Timestep operator*(const Timestep& lhs, const Timestep& rhs)
	{
		return lhs.getSeconds() * rhs.getSeconds();
	}

	float operator+(const Timestep& lhs, const float& rhs)
	{
		return lhs.getSeconds() + rhs;
	}

	float operator-(const Timestep& lhs, const float& rhs)
	{
		return lhs.getSeconds() - rhs;
	}

	float operator*(const Timestep& lhs, const float& rhs)
	{
		return lhs.getSeconds() * rhs;
	}

	float operator/(const Timestep& lhs, const float& rhs)
	{
		return lhs.getSeconds() / rhs;
	}

	Transform* Transform_Factory1()
	{
		return new Transform(glm::vec2(0), 0, glm::vec2(0));
	}

	// ---------- GLM - Vec2 ----------

	glm::vec2* Vec2Default() {
		return new glm::vec2(1.0);
	}

	glm::vec2* Vec2Copy(const glm::vec2& in) {
		return new glm::vec2(in);
	}

	glm::vec2* Vec2Init1(float x) {
		return new glm::vec2(x);
	}

	glm::vec2* Vec2Init2(float x, float y) {
		return new glm::vec2(x, y);
	}

	
}