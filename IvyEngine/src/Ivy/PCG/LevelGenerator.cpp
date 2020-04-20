#include "ivypch.h"

#include "LevelGenerator.h"

#include "../ECS/ECS.h"

namespace Ivy 
{
	LevelGenerator::LevelGenerator()
	{
		this->generator = FI2Pop();
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
					if (x == 0)
					{
						borderPosition.x -= wallOfsset;
					}
					else
					{
						borderPosition.x += wallOfsset;
					}
					Entity entity = ECS::getInstance().createEntity();
					ECS::getInstance().addComponent<Tag>(entity, Tag("WallVertical" + std::to_string(entity)));
					ECS::getInstance().addComponent<Transform>(entity, Transform(borderPosition, 0.0f, glm::vec2(1.0f, 8.0f)));
					ECS::getInstance().addComponent<Renderable>(entity, Renderable("verticalBorder.png"));
					ECS::getInstance().addComponent<CollidableBox>(entity, CollidableBox(borderPosition, 0.0f, glm::vec2(1.0f, 8.0f)));
				}
				if (y == 0 || y == (int)yMax - 1)
				{
					glm::vec2 borderPosition;
					borderPosition.x = (x * positionOffset) - (xMax * positionOffset) / 2;
					borderPosition.y =  (y * positionOffset) - (yMax * positionOffset) / 2;
					if (y == 0)
					{
						borderPosition.y -= wallOfsset;
					}
					else
					{
						borderPosition.y += wallOfsset;
					}
					Entity entity = ECS::getInstance().createEntity();
					ECS::getInstance().addComponent<Tag>(entity, Tag("WallHorizontal" + std::to_string(entity)));
					ECS::getInstance().addComponent<Transform>(entity, Transform(borderPosition, 0.0f, glm::vec2(8.0f, 1.0f)));
					ECS::getInstance().addComponent<Renderable>(entity, Renderable("horizontalBorder.png"));
					ECS::getInstance().addComponent<CollidableBox>(entity, CollidableBox(borderPosition, 0.0f, glm::vec2(8.0f, 1.0f)));
				}

				if (it != fittest.getDesignElements().end())
				{
					DesignElement& levelElement = *it;
					ElementType type = levelElement.getElementType();
					Entity entity = ECS::getInstance().createEntity();
					levelElement.transform.position.x = (x * positionOffset) - (xMax * positionOffset) / 2;
					levelElement.transform.position.y = (y * positionOffset) - (yMax * positionOffset) / 2;
					switch (type)
					{
					case ElementType::Hallway:
						IVY_CORE_TRACE("Adding Hallway, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("hallway.png"));
						break;
					case ElementType::VerticalWall:
						IVY_CORE_TRACE("Adding VerticalWall Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("verticalWall.png"));
						break;
					case ElementType::HorizontalWall:
						IVY_CORE_TRACE("Adding HorizontalWall Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("horizontalWall.png"));
						break;
					case ElementType::Pillar:
						IVY_CORE_TRACE("Adding Pillar Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("pillar.png"));
						break;
					case ElementType::Hole:
						IVY_CORE_TRACE("Adding Hole Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("hole.png"));
						break;
					case ElementType::RangedEnemy:
						IVY_CORE_TRACE("Adding RangedEnemy Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("rangedEnemy.png"));
						break;
					case ElementType::StandardRoom1:
						IVY_CORE_TRACE("Adding StandardRoom1, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("standardRoom1.png"));
						break;
					case ElementType::StandardRoom2:
						IVY_CORE_TRACE("Adding StandardRoom2, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("standardRoom2.png"));
						break;
					case ElementType::TShaped:
						IVY_CORE_TRACE("Adding TShaped, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("tshape.png"));
						break;
					case ElementType::ClosedRoom:
						IVY_CORE_TRACE("Adding ClosedRoom, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable("closedRoom.png"));
						break;
					default:
						IVY_CORE_WARN("Default Generation Case! Type={0}", std::to_string(type));
					}
					IVY_CORE_TRACE("Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", entity, levelElement.tag.tag, 
						levelElement.transform.position.x, levelElement.transform.position.y, levelElement.transform.rotation, 
						levelElement.transform.scale.x, levelElement.transform.scale.y);
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