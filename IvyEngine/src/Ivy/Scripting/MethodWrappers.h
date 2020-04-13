#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

#include "../ECS/ECS.h"
#include "../ECS/Components/Transform.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/Renderable.h"
#include "../ECS/Components/Collidable.h"

#include "../Core/InputHandler.h"
#include "../Core/Logger.h"
#include "../Core/ResourcePaths.h"
#include "../Core/Timestep.h"

#include "ScriptableObject.h"

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


	// ---------- Components ----------
	Transform& FindTransform(Entity entity) {
		return ECS::getInstance().getComponent<Transform>(entity);
	}

	Transform* Transform_Factory1()
	{
		return new Transform(glm::vec2(0), 0, glm::vec2(0));
	}

	Renderable& FindRenderable(Entity entity)
	{
		return ECS::getInstance().getComponent<Renderable>(entity);
	}

	Renderable* Renderable_Factory1()
	{
		return new Renderable(Paths::baseTexturePath.string());
	}

	CollidableBox& FindCollidable(Entity entity)
	{
		return ECS::getInstance().getComponent<CollidableBox>(entity);
	}

	CollidableBox* Collidable_Factory1()
	{
		return new CollidableBox(glm::vec2(0), 0, glm::vec2(0));
	}

	ScriptableObject* FindObjectByTag(const std::string& tag)
	{
		for (Entity entity : ECS::getInstance().getEntities())
		{
			if (ECS::getInstance().getComponent<Tag>(entity).tag == tag)
				return &ECS::getInstance().getComponent<ScriptComponent>(entity).scriptableObject;
		}
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

	bool IsEntityCollidingCollidable(Entity e1, CollidableBox& c1)
	{
		return c1.isCollidingWith.find(e1) != c1.isCollidingWith.end();
	}

	bool AreEntitiesColliding(Entity e1, Entity e2)
	{
		CollidableBox c1 = ECS::getInstance().getComponent<CollidableBox>(e1);
		bool col = c1.isCollidingWith.find(e2) != c1.isCollidingWith.end();
		if (col)
			IVY_CORE_ERROR("MethodWrappers: Colliding: {0} with {1}", e1, e2);
		return col;
	}

	bool AreCollidablesColliding(CollidableBox& c1, CollidableBox& c2)
	{
		return c1.isCollidingWith.find(c2.getEntityId()) != c1.isCollidingWith.end();
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