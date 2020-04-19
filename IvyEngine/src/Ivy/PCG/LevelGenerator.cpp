#include "ivypch.h"
#include "LevelGenerator.h"
#include "../ECS/ECS.h"

namespace Ivy 
{
	LevelGenerator::LevelGenerator()
	{
		this->graph = Graph();
		this->generator = FI2Pop(&graph);
		
	}

	void LevelGenerator::run()
	{
		generator.run();
		finalPopulation = generator.getInfeasiblePopulation();
		fittest = finalPopulation.getFittestIndividual();
		float xMax = (int)std::sqrtf(fittest.getDesignElements().size());
		float yMax = (int)(fittest.getDesignElements().size() / xMax);
		IVY_CORE_INFO("LevelGenerator: xMax={0}, yMax={1}", xMax, yMax);
		auto& it = fittest.getDesignElements().begin();
		for (int x = 0; x < (int)xMax; x++)
		{
			for (int y = 0; y < (int)yMax; y++)
			{
				if (x == 0 || x == (int)xMax-1)
				{
					glm::vec2 borderPosition;
					borderPosition.x = (x * positionOffset) - (xMax * positionOffset) / 2;
					borderPosition.y = (y * positionOffset) - (yMax * positionOffset) / 2;
					//THIS
					if (x == 0)
					{
						borderPosition.x -= wallOfsset;
					}
					else
					{
						borderPosition.x += wallOfsset;
					}
					Entity entity = ECS::getInstance().createEntity();
					ECS::getInstance().addComponent<Tag>(entity, Tag("WallVertical" + entity));
					ECS::getInstance().addComponent<Transform>(entity, Transform(borderPosition, 0.0f, glm::vec2(1.0f, 8.0f)));
					ECS::getInstance().addComponent<Renderable>(entity, Renderable("verticalBorder.png"));
					ECS::getInstance().addComponent<CollidableBox>(entity, CollidableBox(borderPosition, 0.0f, glm::vec2(1.0f, 8.0f)));
				}
				if (y == 0 || y == (int)yMax - 1)
				{
					glm::vec2 borderPosition;
					borderPosition.x = (x * positionOffset) - (xMax * positionOffset) / 2;
					borderPosition.y =  (y * positionOffset) - (yMax * positionOffset) / 2;
					// THIS
					if (y == 0)
					{
						borderPosition.y -= wallOfsset;
					}
					else
					{
						borderPosition.y += wallOfsset;
					}
					Entity entity = ECS::getInstance().createEntity();
					ECS::getInstance().addComponent<Tag>(entity, Tag("WallHorizontal" + entity));
					ECS::getInstance().addComponent<Transform>(entity, Transform(borderPosition, 0.0f, glm::vec2(8.0f, 1.0f)));
					ECS::getInstance().addComponent<Renderable>(entity, Renderable("horizontalBorder.png"));
					ECS::getInstance().addComponent<CollidableBox>(entity, CollidableBox(borderPosition, 0.0f, glm::vec2(8.0f, 1.0f)));
				}
				if (it != fittest.getDesignElements().end())
				{
					DesignElement* designElement = *it;
					LevelElement* levelElement = (LevelElement*)designElement;
					ElementType type = levelElement->getElementType();
					Entity entity = ECS::getInstance().createEntity();
					levelElement->transform.position.x = (x * positionOffset) - (xMax * positionOffset) / 2;
					levelElement->transform.position.y = (y * positionOffset) - (yMax * positionOffset) / 2;
					switch (type)
					{
					case ElementType::Hallway:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("hallway.png"));
						break;
					case ElementType::VerticalWall:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("verticalWall.png"));
						break;
					case ElementType::HorizontalWall:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("horizontalWall.png"));
						break;
					case ElementType::Pillar:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("pillar.png"));
						break;
					case ElementType::Hole:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("hole.png"));
						break;
					case ElementType::RangedEnemy:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("rangedEnemy.png"));
					case ElementType::StandardRoom1:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("standardRoom1.png"));
						break;
					case ElementType::StandardRoom2:
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("standardRoom2.png"));
						break;
					}
				}
				else
				{
					break;
				}
				it++;
			}
		}
		

	}

}