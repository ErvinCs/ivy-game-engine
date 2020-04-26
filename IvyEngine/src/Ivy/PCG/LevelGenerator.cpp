#include "ivypch.h"

#include "LevelGenerator.h"

#include "../ECS/ECS.h"
#include "../Scripting/ScriptManager.h"

namespace Ivy 
{
	int LevelGenerator::alwaysLoadFittest = 0;
	bool LevelGenerator::alwaysLoad = false;
	bool LevelGenerator::isGenerating = false;

	std::string LevelGenerator::horizontalBorderPath = "horizontalBorder.png";
	std::string LevelGenerator::verticalBorderPath = "verticalBorder.png";
	std::string LevelGenerator::closedRoomPath = "closedRoom.png";
	std::string LevelGenerator::enemyFlyPath = "enemy-fly.png";
	std::string LevelGenerator::enemyGroundPath = "enemy-ground.png";
	std::string LevelGenerator::hallwayPath = "hallway.png";
	std::string LevelGenerator::holePath = "hole.png";
	std::string LevelGenerator::horizontalWallPath = "horizontalWall.png";
	std::string LevelGenerator::verticalWallPath = "verticalWall.png";
	std::string LevelGenerator::pillarPath = "pillar.png";
	std::string LevelGenerator::meleeEnemyPath = "meleeEnemy.png";
	std::string LevelGenerator::rangedEnemyPath = "rangedEnemy.png";
	std::string LevelGenerator::stdRoom1Path = "standardRoom1.png";
	std::string LevelGenerator::stdRoom2Path = "standardRoom2.png";
	std::string LevelGenerator::tShapePath = "tshape.png";
	std::string LevelGenerator::scriptPatrolV = "patrol-v.as";
	std::string LevelGenerator::scriptPatrolH = "patrol-h.as";
	std::string LevelGenerator::playerScript = "player.as";
	std::string LevelGenerator::playerPath = "ninja.png";

	

	LevelGenerator::LevelGenerator()
	{
		this->generator = FI2Pop();
	}

	void LevelGenerator::run()
	{
		generator.init();
		LevelGenerator::isGenerating = true;
		generator.run();
		if (!generator.getInitialisedFeasible())
		{
			fittest = generator.getFittestInfeasibleIndividual();
			IVY_CORE_INFO("LevelGenerator: Loading Fittest Infeasible");
			
		}
		else
		{
			if (alwaysLoad)
			{
				if (alwaysLoadFittest == 1)
				{
					IVY_CORE_INFO("LevelGenerator: Loading Fittest Feasible");
					fittest = generator.getFittestFeasibleIndividual();
				}
				else
				{
					IVY_CORE_INFO("LevelGenerator: Loading Least fit Feasible");
					fittest = generator.getLeastFitFeasibleIndividual();
				}				
			}
			else
			{
				fittest = generator.getRandomFeasibleIndividual();
				IVY_CORE_INFO("LevelGenerator: Loading Random Feasbile");
			}
			
		}
		float xMax = (int)std::sqrtf(fittest.getDesignElements().size());
		float yMax = (int)(fittest.getDesignElements().size() / xMax);
		IVY_CORE_INFO("LevelGenerator: xMax={0}, yMax={1}", xMax, yMax);
		Entity wall1 = -1, wall2 = -1, wall3 = -1, wall4 = -1, hole = -1, enemy1 = -1, enemy2 = -1, enemy3 = -1;
		uint16_t enemyTagCounter = 0;

		// Spawn the player
		Entity player = ECS::getInstance().createEntity();
		ECS::getInstance().addComponent<Tag>(player, Tag("Player"));
		Transform playerTransform = Transform(
			glm::vec2(-(xMax * positionOffset) / 2, -(yMax * positionOffset) / 2), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
		);
		CollidableBox playerBox = CollidableBox(playerTransform.position, playerTransform.rotation, playerTransform.scale);
		playerBox.isTrigger = false;
		ECS::getInstance().addComponent<Transform>(player, playerTransform);
		ECS::getInstance().addComponent<Renderable>(player, Renderable(LevelGenerator::playerPath));
		ECS::getInstance().addComponent<CollidableBox>(player, playerBox);
		ECS::getInstance().addComponent<ScriptComponent>(player, ScriptComponent(LevelGenerator::playerScript));
		ScriptManager::GetInstance().createScriptController(
			(Paths::scriptsPath / LevelGenerator::playerScript).string(), &ECS::getInstance().getComponent<ScriptComponent>(player).scriptableObject, player
		);

		// Spawn Enemies
		auto& it = fittest.getDesignElements().begin();
		for (int x = 0; x < (int)xMax; x++)
		{
			for (int y = 0; y < (int)yMax; y++)
			{
				if (it != fittest.getDesignElements().end())
				{
					DesignElement& levelElement = *it;
					ElementType type = levelElement.getElementType();
					levelElement.transform.position.x = (x * positionOffset) - (xMax * positionOffset) / 2;
					levelElement.transform.position.y = (y * positionOffset) - (yMax * positionOffset) / 2;
					switch (type)
					{
					case ElementType::VerticalWall:
						IVY_CORE_TRACE("Adding VerticalWall Enemies");
						// Enemies
						{
							enemy1 = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy1, Tag(std::string("Enemy-Fly-" + std::to_string(enemyTagCounter++))));
							Transform fly1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox fly1box = CollidableBox(fly1Transform.position, fly1Transform.rotation, fly1Transform.scale);
							fly1box.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy1, fly1Transform);
							ECS::getInstance().addComponent<Renderable>(enemy1, Renderable(LevelGenerator::enemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy1, fly1box);
							ECS::getInstance().addComponent<ScriptComponent>(enemy1, ScriptComponent(LevelGenerator::scriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::scriptsPath / LevelGenerator::scriptPatrolH).string(), &ECS::getInstance().getComponent<ScriptComponent>(enemy1).scriptableObject, enemy1
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy1,
								ECS::getInstance().getComponent<Tag>(enemy1).tag,
								fly1Transform.position.x, fly1Transform.position.y + halfTilePos, fly1Transform.rotation, fly1Transform.scale.x, fly1Transform.scale.y);
						}
						break;
					case ElementType::HorizontalWall:
						//IVY_CORE_TRACE("Adding HorizontalWall Enemies");
						// Enemies
						break;
					case ElementType::Pillar:
						//IVY_CORE_TRACE("Adding Pillar Enemies");
						// Enemies
						break;
					case ElementType::Hole:
						//IVY_CORE_TRACE("Adding Hole Enemies");
						// Enemies
						break;
					case ElementType::RangedEnemy:
						IVY_CORE_TRACE("Adding RangedEnemy Enemies");
						// Enemies
						{
							enemy1 = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy1, Tag(std::string("Enemy-Fly-" + std::to_string(enemyTagCounter++))));
							Transform fly2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 2, levelElement.transform.position.y + halfTilePos * 6), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox fly2Box = CollidableBox(fly2Transform.position, fly2Transform.rotation, fly2Transform.scale);
							fly2Box.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy1, fly2Transform);
							ECS::getInstance().addComponent<Renderable>(enemy1, Renderable(LevelGenerator::enemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy1, fly2Box);
							ECS::getInstance().addComponent<ScriptComponent>(enemy1, ScriptComponent(LevelGenerator::scriptPatrolV));
							ScriptManager::GetInstance().createScriptController(
								(Paths::scriptsPath / LevelGenerator::scriptPatrolV).string(), &ECS::getInstance().getComponent<ScriptComponent>(enemy1).scriptableObject, enemy1
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy1,
								ECS::getInstance().getComponent<Tag>(enemy1).tag,
								fly2Transform.position.x + halfTilePos, fly2Transform.position.y + halfTilePos, fly2Transform.rotation, fly2Transform.scale.x, fly2Transform.scale.y);

							enemy2 = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy2, Tag(std::string("Enemy-Fly-" + std::to_string(enemyTagCounter++))));
							Transform fly3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 2, levelElement.transform.position.y - halfTilePos * 6), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox fly3Box = CollidableBox(fly3Transform.position, fly3Transform.rotation, fly3Transform.scale);
							fly3Box.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy2, fly3Transform);
							ECS::getInstance().addComponent<Renderable>(enemy2, Renderable(LevelGenerator::enemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy2, CollidableBox(fly3Transform.position, fly3Transform.rotation, fly3Transform.scale));
							ECS::getInstance().addComponent<ScriptComponent>(enemy2, ScriptComponent(LevelGenerator::scriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::scriptsPath / LevelGenerator::scriptPatrolH).string(), &ECS::getInstance().getComponent<ScriptComponent>(enemy2).scriptableObject, enemy2
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy2,
								ECS::getInstance().getComponent<Tag>(enemy2).tag,
								fly2Transform.position.x - halfTilePos * 2, fly2Transform.position.y - halfTilePos * 2, fly2Transform.rotation, fly2Transform.scale.x, fly2Transform.scale.y);
						}
						break;
					case ElementType::TShaped:
						IVY_CORE_TRACE("Adding TShaped Enemies");
						// Enemies
						{
							enemy1 = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy1, Tag(std::string("Enemy-Ground-" + std::to_string(enemyTagCounter++))));
							Transform ground1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 2), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox ground1box = CollidableBox(ground1Transform.position, ground1Transform.rotation, ground1Transform.scale);
							ground1box.isTrigger = false;
							ECS::getInstance().addComponent<Transform>(enemy1, ground1Transform);
							ECS::getInstance().addComponent<Renderable>(enemy1, Renderable(LevelGenerator::enemyGroundPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy1, ground1box);
							ECS::getInstance().addComponent<ScriptComponent>(enemy1, ScriptComponent(LevelGenerator::scriptPatrolV));
							ScriptManager::GetInstance().createScriptController(
								(Paths::scriptsPath / LevelGenerator::scriptPatrolV).string(), &ECS::getInstance().getComponent<ScriptComponent>(enemy1).scriptableObject, enemy1
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy1,
								ECS::getInstance().getComponent<Tag>(enemy1).tag,
								ground1Transform.position.x, ground1Transform.position.y - halfTilePos * 2, ground1Transform.rotation, ground1Transform.scale.x, ground1Transform.scale.y);

							enemy2 = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy2, Tag(std::string("Enemy-Fly-" + std::to_string(enemyTagCounter++))));
							Transform fly4Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 2, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox fly4box = CollidableBox(fly4Transform.position, fly4Transform.rotation, fly4Transform.scale);
							fly4box.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy2, fly4Transform);
							ECS::getInstance().addComponent<Renderable>(enemy2, Renderable(LevelGenerator::enemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy2, fly4box);
							ECS::getInstance().addComponent<ScriptComponent>(enemy2, ScriptComponent(LevelGenerator::scriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::scriptsPath / LevelGenerator::scriptPatrolH).string(), &ECS::getInstance().getComponent<ScriptComponent>(enemy2).scriptableObject, enemy2
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy2,
								ECS::getInstance().getComponent<Tag>(enemy2).tag,
								fly4Transform.position.x - halfTilePos * 2, fly4Transform.position.y + halfTilePos, fly4Transform.rotation, fly4Transform.scale.x, fly4Transform.scale.y);

							enemy3 = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy3, Tag(std::string("Enemy-Fly-" + std::to_string(enemyTagCounter++))));
							Transform fly5Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 2, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox fly5box = CollidableBox(fly5Transform.position, fly5Transform.rotation, fly5Transform.scale);
							fly5box.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy3, fly5Transform);
							ECS::getInstance().addComponent<Renderable>(enemy3, Renderable(LevelGenerator::enemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy3, fly5box);
							ECS::getInstance().addComponent<ScriptComponent>(enemy3, ScriptComponent(LevelGenerator::scriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::scriptsPath / LevelGenerator::scriptPatrolH).string(), &ECS::getInstance().getComponent<ScriptComponent>(enemy3).scriptableObject, enemy3
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy3,
								ECS::getInstance().getComponent<Tag>(enemy3).tag,
								fly5Transform.position.x + halfTilePos * 2, fly5Transform.position.y + halfTilePos, fly5Transform.rotation, fly5Transform.scale.x, fly5Transform.scale.y);
						}
						break;
					case ElementType::ClosedRoom:
						//IVY_CORE_TRACE("Adding ClosedRoom Enemies");
						// Enemies
						break;
					case ElementType::MeleeEnemy:
						//IVY_CORE_TRACE("Adding MeleeEnemy Enemies");
						//Enemies
						break;
					default:
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

		// Spawn Environment
		it = fittest.getDesignElements().begin();
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
					ECS::getInstance().addComponent<Tag>(entity, Tag("Border Vertical" + std::to_string(entity)));
					ECS::getInstance().addComponent<Transform>(entity, Transform(borderPosition, 0.0f, glm::vec2(1.0f, 8.0f)));
					ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::verticalBorderPath));
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
					ECS::getInstance().addComponent<Tag>(entity, Tag("Border Horizontal" + std::to_string(entity)));
					ECS::getInstance().addComponent<Transform>(entity, Transform(borderPosition, 0.0f, glm::vec2(8.0f, 1.0f)));
					ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::horizontalBorderPath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::hallwayPath));
						// Environment
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2 || levelElement.transform.rotation == 3 * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - 5 * halfTilePos, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 3.0f, halfTileSize * 8.0f));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + 5 * halfTilePos, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 3.0f, halfTileSize * 8.0f));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - 5 * halfTilePos), 0, glm::vec2(halfTileSize * 8.0f, halfTileSize * 3.0f));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + 5 * halfTilePos), 0, glm::vec2(halfTileSize * 8.0f, halfTileSize * 3.0f));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						break;
					case ElementType::VerticalWall:
						IVY_CORE_TRACE("Adding VerticalWall Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::verticalWallPath));
						// Environment
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						wall3 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8.0f));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos, levelElement.transform.position.y - halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos, levelElement.transform.position.y + halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == (float)M_PI)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + 7 * halfTilePos), 0, glm::vec2(halfTileSize * 8.0f, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize * 3, levelElement.transform.position.y - halfTileSize), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTileSize * 3, levelElement.transform.position.y - halfTileSize), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == 3 * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8.0f));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize, levelElement.transform.position.y - halfTileSize * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize, levelElement.transform.position.y + halfTileSize * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else 
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 8.0f, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 3, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 3, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						break;
					case ElementType::HorizontalWall:
						IVY_CORE_TRACE("Adding HorizontalWall Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::horizontalWallPath));
						// Environment
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						wall3 = ECS::getInstance().createEntity();
						wall4 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2 || levelElement.transform.rotation == 3.0f * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 3, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 3));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 3, levelElement.transform.position.y - halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 3));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 5, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall4Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 5, levelElement.transform.position.y + halfTilePos * 7), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall4, CollidableBox(wall4Transform.position, wall4Transform.rotation, wall4Transform.scale));

						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos, levelElement.transform.position.y + halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos, levelElement.transform.position.y - halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y - halfTilePos * 5), 0, glm::vec2(halfTileSize, halfTileSize * 3));
							Transform wall4Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y + halfTilePos * 5), 0, glm::vec2(halfTileSize, halfTileSize * 3));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall4, CollidableBox(wall4Transform.position, wall4Transform.rotation, wall4Transform.scale));

						}
						break;
					case ElementType::Pillar:
						IVY_CORE_TRACE("Adding Pillar Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::pillarPath));
						// Environment
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						wall3 = ECS::getInstance().createEntity();
						{
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						if (levelElement.transform.rotation == (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 7));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						else if (levelElement.transform.rotation == (float)M_PI)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos, levelElement.transform.position.y + 7 * halfTilePos), 0, glm::vec2(halfTileSize * 7, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						else if (levelElement.transform.rotation == 3.0f * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos, levelElement.transform.position.y + halfTilePos * 7), 0, glm::vec2(halfTileSize * 7, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 7));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						break;
					case ElementType::Hole:
						IVY_CORE_TRACE("Adding Hole Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::holePath));
						// Environment
						hole = ECS::getInstance().createEntity();
						{
							Transform holeTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 4, halfTileSize * 4));
							ECS::getInstance().addComponent<CollidableBox>(hole, CollidableBox(holeTransform.position, holeTransform.rotation, holeTransform.scale));
						}
						break;
					case ElementType::RangedEnemy:
						IVY_CORE_TRACE("Adding RangedEnemy Room, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::rangedEnemyPath));
						// Environment
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2 || levelElement.transform.rotation == 3.0f * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 3, levelElement.transform.position.y - halfTilePos * 3), 0, glm::vec2(halfTileSize, halfTileSize * 3));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 3, levelElement.transform.position.y + halfTilePos * 3), 0, glm::vec2(halfTileSize, halfTileSize * 3));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 3, levelElement.transform.position.y + halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 3, levelElement.transform.position.y - halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
						}
						break;
					case ElementType::StandardRoom1:
						IVY_CORE_TRACE("Adding StandardRoom1, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::stdRoom1Path));
						// Environment
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						wall3 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 3, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 2));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos, levelElement.transform.position.y - halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos, levelElement.transform.position.y + halfTilePos * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == (float)M_PI)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 3), 0, glm::vec2(halfTileSize * 2, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize * 3, levelElement.transform.position.y - halfTileSize), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTileSize * 3, levelElement.transform.position.y - halfTileSize), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == 3.0f * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 3), 0, glm::vec2(halfTileSize, halfTileSize * 2));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize, levelElement.transform.position.y - halfTileSize * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize, levelElement.transform.position.y + halfTileSize * 3), 0, glm::vec2(halfTileSize * 3, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 3), 0, glm::vec2(halfTileSize * 2, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 3, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 3, levelElement.transform.position.y + halfTilePos), 0, glm::vec2(halfTileSize, halfTileSize * 3.0f));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						break;
					case ElementType::StandardRoom2:
						IVY_CORE_TRACE("Adding StandardRoom2, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::stdRoom2Path));
						// Empty
						break;
					case ElementType::TShaped:
						IVY_CORE_TRACE("Adding TShaped, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::tShapePath));
						// Environment
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						wall3 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 6, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 2, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 5, levelElement.transform.position.y - halfTilePos * 6), 0, glm::vec2(halfTileSize * 3, halfTileSize * 2));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 5, levelElement.transform.position.y + halfTilePos * 6), 0, glm::vec2(halfTileSize * 3, halfTileSize * 2));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == (float)M_PI)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 6), 0, glm::vec2(halfTileSize * 8, halfTileSize * 2));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 6, levelElement.transform.position.y + halfTilePos * 5), 0, glm::vec2(halfTileSize * 2, halfTileSize * 3));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 6, levelElement.transform.position.y + halfTilePos * 5), 0, glm::vec2(halfTileSize * 2, halfTileSize * 3));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == 3.0f * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 6, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 2, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 5, levelElement.transform.position.y - halfTilePos * 6), 0, glm::vec2(halfTileSize * 3, halfTileSize * 2));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 5, levelElement.transform.position.y + halfTilePos * 6), 0, glm::vec2(halfTileSize * 3, halfTileSize * 2));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 6), 0, glm::vec2(halfTileSize * 8, halfTileSize * 2));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 6, levelElement.transform.position.y - halfTilePos * 5), 0, glm::vec2(halfTileSize * 2, halfTileSize * 3));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 6, levelElement.transform.position.y - halfTilePos * 5), 0, glm::vec2(halfTileSize * 2, halfTileSize * 3));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						break;
					case ElementType::ClosedRoom:
						IVY_CORE_TRACE("Adding ClosedRoom, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::closedRoomPath));
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						wall3 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + 7 * halfTileSize), 0, glm::vec2(halfTileSize * 6, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == (float)M_PI)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTileSize * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 6));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == 3.0f * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTileSize * 7), 0, glm::vec2(halfTileSize * 6, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 6));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						break;
					case ElementType::MeleeEnemy:
						IVY_CORE_TRACE("Adding MeleeEnemy, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::meleeEnemyPath));
						wall1 = ECS::getInstance().createEntity();
						wall2 = ECS::getInstance().createEntity();
						wall3 = ECS::getInstance().createEntity();
						if (levelElement.transform.rotation == (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + 7 * halfTileSize), 0, glm::vec2(halfTileSize * 6, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == (float)M_PI)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTileSize * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 6));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else if (levelElement.transform.rotation == 3.0f * (float)M_PI_2)
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 8));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTileSize * 7), 0, glm::vec2(halfTileSize * 6, halfTileSize));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						else
						{
							Transform wall1Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall2Transform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 7), 0, glm::vec2(halfTileSize * 8, halfTileSize));
							Transform wall3Transform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTileSize * 7, levelElement.transform.position.y), 0, glm::vec2(halfTileSize, halfTileSize * 6));
							ECS::getInstance().addComponent<CollidableBox>(wall1, CollidableBox(wall1Transform.position, wall1Transform.rotation, wall1Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall2, CollidableBox(wall2Transform.position, wall2Transform.rotation, wall2Transform.scale));
							ECS::getInstance().addComponent<CollidableBox>(wall3, CollidableBox(wall3Transform.position, wall3Transform.rotation, wall3Transform.scale));
						}
						break;
					default:
						IVY_CORE_WARN("LevelGenerator: Default Generation Case! Type={0}", std::to_string(type));
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
		LevelGenerator::isGenerating = false;
	}

}