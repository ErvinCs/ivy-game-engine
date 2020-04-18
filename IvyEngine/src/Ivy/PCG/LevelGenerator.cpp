#include "ivypch.h"
#include "LevelGenerator.h"
#include "../ECS/ECS.h"

namespace Ivy 
{

	LevelGenerator::LevelGenerator(const FI2Pop& generator)
	{
		this->generator = generator;
	}

	void LevelGenerator::run()
	{
		generator.run();
		finalPopulation = generator.getInfeasiblePopulation();
		fittest = finalPopulation.getFittestIndividual();
		for (auto& it = fittest.getDesignElements().begin(); it != fittest.getDesignElements().end(); it++)
		{
			DesignElement* designElement = *it;
			LevelElement* levelElement = (LevelElement*)designElement;
			ElementType type = levelElement->getElementType();
			Entity entity = ECS::getInstance().createEntity();
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
				ECS::getInstance().addComponent<Renderable>(entity, Renderable("jmp-enemy.png"));
				break;
			default:
				ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement->tag));
				ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement->transform));
				ECS::getInstance().addComponent<Renderable>(entity, Renderable("ramen.png"));
			}
		}

	}

}