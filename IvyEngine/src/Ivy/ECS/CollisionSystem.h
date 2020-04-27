#pragma once

#include <stdint.h>
#include <glm/glm.hpp>

#include "System.h"
#include "Entity.h"

#include "Components/Collidable.h"
#include "Components/Transform.h"

namespace Ivy {

	class CollisionSystem : public System
	{
	private:
		float maxDistA;
		float maxDistB;
	public:
		static int mapSizeX, mapSizeY, tileSize;
		static int tileInitialCapacity;
		static std::vector<std::vector<std::vector<Entity>>> tileArray;

		CollisionSystem() = default;
		CollisionSystem(EntityContainer& entities)
		{
			this->setEntities(entities);
		}

		virtual void init() override;
		virtual void update(float deltatime) override;
		void parseTile(int i, int j, Entity it, CollidableBox* A, Transform* ATransform, glm::vec2* oldPosition);
		static void ConstructArray();
	};

}