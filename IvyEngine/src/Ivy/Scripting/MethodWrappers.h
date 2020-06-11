#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

#include "../ECS/ECS.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/Renderable.h"
#include "../ECS/Components/Collidable.h"
#include "../ECS/Systems/CollisionSystem.h"

#include "../Core/InputHandler.h"
#include "../Core/Logger.h"
#include "../Core/ResourcePaths.h"
#include "../Core/Timestep.h"

#include "ScriptableObject.h"

namespace Ivy {
	/**
	 * Method wrappers for functions made available with AS's Scripting Enveironment.
	 */

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

	// ---------- ScriptableObject ----------

	ScriptableObject* FindObjectByTag(const std::string& tag)
	{
		bool found = false;
		for (Entity entity : ECS::getInstance().getEntities())
		{
			if (ECS::getInstance().getComponent<Tag>(entity).tag == tag)
			{
				found = true;
				if (ECS::getInstance().getComponent<ScriptComponent>(entity).getComponentId() != ECS::getInstance().getComponentTypes().find(typeid(ScriptComponent).name())->second)
				{
					return NULL;
				}
				else
				{
					return ECS::getInstance().getComponent<ScriptComponent>(entity).scriptableObject;
				}

			}
		}
		if (!found)
		{
			return NULL;
		}
	}

	// ---------- Components ----------
	Transform* FindTransform(Entity entity) {
		Transform* t = &ECS::getInstance().getComponent<Transform>(entity);
		if (t->getComponentId() == 0)
			return NULL;
		else
			return t;
	}

	Transform* Transform_Factory1()
	{
		return new Transform(glm::vec2(0), 0, glm::vec2(0));
	}

	Transform* Transform_Factory2(glm::vec2 position, float rotation, glm::vec2 scale)
	{
		return new Transform(position, rotation, scale);
	}

	Renderable* FindRenderable(Entity entity)
	{
		Renderable* r = &ECS::getInstance().getComponent<Renderable>(entity);
		if (r->getComponentId() == 0)
			return NULL;
		else
			return r;
	}

	Renderable* Renderable_Factory1()
	{
		return new Renderable(Paths::baseTexturePath.string());
	}

	CollidableBox* FindCollidable(Entity entity)
	{
		CollidableBox* c = &ECS::getInstance().getComponent<CollidableBox>(entity);
		if (c->getComponentId() == 0)
			return NULL;
		else
			return c;
	}

	CollidableBox* Collidable_Factory1()
	{
		return new CollidableBox(glm::vec2(0), 0, glm::vec2(0));
	}

	void Rotate90Transform(Transform& transform)
	{
		transform.rotation += M_PI_2;
	}

	void Rotate180Transform(Transform& transform)
	{
		transform.rotation += M_PI;
	}

	void Rotate270Transform(Transform& transform)
	{
		transform.rotation += 3.0f * M_PI_2;
	}

	void Rotate90Collidable(CollidableBox& collidable)
	{
		collidable.rotation += M_PI_2;
	}

	void Rotate180Collidable(CollidableBox& collidable)
	{
		collidable.rotation += M_PI;
	}

	void Rotate270Collidable(CollidableBox& collidable)
	{
		collidable.rotation += 3.0f * M_PI_2;
	}

	bool AreEntitiesColliding(Entity e1, Entity e2)
	{
		return std::find(CollisionSystem::isCollidingWith[e1].begin(), CollisionSystem::isCollidingWith[e1].end(), e2) != CollisionSystem::isCollidingWith[e1].end();
	}

	bool IsEntityColliding(Entity e)
	{
		return CollisionSystem::isCollidingWith[e].size() != 0;
	}

	void FlipX(Renderable& renderable)
	{
		renderable.texture->flipX();
	}

	void FlipY(Renderable& renderable)
	{
		renderable.texture->flipY();
	}

	void LoadNewTextureToEntity(Entity entity, std::string newPath)
	{
		Renderable* r = &ECS::getInstance().getComponent<Renderable>(entity);
		r->spritePath = newPath;
		r->texture = Texture::Create(newPath);
	}

	void LoadNewTextureToRenderable(Renderable& r, std::string newPath)
	{
		r.spritePath = newPath;
		r.texture = Texture::Create(newPath);
	}

	void SelfDestroyRenderable(Entity entity)
	{
		Renderable* r = &ECS::getInstance().getComponent<Renderable>(entity);
		if (r->getComponentId() == 0)
			return;
		else
			ECS::getInstance().removeComponent<Renderable>(entity);
	}

	void SelfDestroyCollidable(Entity entity)
	{
		CollidableBox* c = &ECS::getInstance().getComponent<CollidableBox>(entity);
		if (c->getComponentId() == 0)
			return;
		else
			ECS::getInstance().removeComponent<CollidableBox>(entity);
	}

	void SelfDestroyTransform(Entity entity)
	{
		Transform* t = &ECS::getInstance().getComponent<Transform>(entity);
		if (t->getComponentId() == 0)
			return;
		else
			ECS::getInstance().removeComponent<Transform>(entity);
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