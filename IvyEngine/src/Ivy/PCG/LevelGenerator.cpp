#include "ivypch.h"

#include "LevelGenerator.h"

#include "../ECS/ECS.h"
#include "../Scripting/ScriptManager.h"
#include "../Core/Application.h"

namespace Ivy 
{
	int LevelGenerator::AlwaysLoadFittest = 0;
	bool LevelGenerator::AlwaysLoad = false;
	bool LevelGenerator::IsGenerating = false;

	std::string LevelGenerator::HorizontalBorderPath = "horizontalBorder.png";
	std::string LevelGenerator::VerticalBorderPath = "verticalBorder.png";
	std::string LevelGenerator::ClosedRoomPath = "closedRoom.png";
	std::string LevelGenerator::HallwayPath = "hallway.png";
	std::string LevelGenerator::HolePath = "hole.png";
	std::string LevelGenerator::HorizontalWallPath = "horizontalWall.png";
	std::string LevelGenerator::VerticalWallPath = "verticalWall.png";
	std::string LevelGenerator::PillarPath = "pillar.png";
	std::string LevelGenerator::MeleeEnemyPath = "meleeEnemy.png";
	std::string LevelGenerator::RangedEnemyPath = "rangedEnemy.png";
	std::string LevelGenerator::StdRoom1Path = "standardRoom1.png";
	std::string LevelGenerator::StdRoom2Path = "standardRoom2.png";
	std::string LevelGenerator::TShapePath = "tshape.png";

	std::string LevelGenerator::EnemyFlyPath = "enemy-1.png";
	std::string LevelGenerator::EnemyGroundPath = "enemy-2.png";
	std::string LevelGenerator::PlayerPath = "player.png";
	std::string LevelGenerator::CollectablePath = "item.png";

	std::string LevelGenerator::ScriptPatrolV = "patrol-diag.as";
	std::string LevelGenerator::ScriptPatrolH = "patrol-plus.as";
	std::string LevelGenerator::PlayerScript = "player.as";
	std::string LevelGenerator::CollectableScript = "item.as";
	

	LevelGenerator::LevelGenerator()
	{
		this->generator = FI2Pop();
	}

	void LevelGenerator::clearPopulations()
	{
		this->generator.clearFeasiblePop();
		this->generator.clearInfeasiblePop();
	}

	void LevelGenerator::run()
	{
		generator.init();
		LevelGenerator::IsGenerating = true;
		generator.run();
		if (!generator.getInitialisedFeasible())
		{
			fittest = generator.getFittestInfeasibleIndividual();
			finalPopulation = generator.getInfeasiblePopulation();
			IVY_CORE_INFO("LevelGenerator: Loading Fittest Infeasible");
			
		}
		else
		{
			finalPopulation = generator.getFeasiblePopulation();
			if (AlwaysLoad)
			{
				if (AlwaysLoadFittest == 1)
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
#ifdef _DEBUG
		float avgDiversity = generator.getFeasiblePopulation().feasibleAvgDiversity();
		float avgFitness = generator.getInfeasiblePopulation().infeasibleAvgFitness();
		IVY_CORE_TRACE("Feasible Average Diversity: {0}", avgDiversity);
		IVY_CORE_TRACE("Inveasible Average Fitness: {0}", avgFitness);
#endif
		float xMax = (int)std::sqrtf(fittest.getDesignElements().size());
		float yMax = (int)(fittest.getDesignElements().size() / xMax);
		IVY_CORE_INFO("LevelGenerator: xMax={0}, yMax={1}", xMax, yMax);
		Entity wall1 = -1, wall2 = -1, wall3 = -1, wall4 = -1, hole = -1, enemy = -1, collectable = -1;
		uint16_t enemyTagCounter = 1;
		uint16_t collectibleTagCounter = 1;

		// Spawn the player
		Entity player = ECS::getInstance().createEntity();
		ECS::getInstance().addComponent<Tag>(player, Tag("Player"));
		Transform playerTransform = Transform(
			glm::vec2(-(xMax * positionOffset) / 2, -(yMax * positionOffset) / 2), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
		);
		CollidableBox playerBox = CollidableBox(playerTransform.position, playerTransform.rotation, playerTransform.scale);
		playerBox.isTrigger = false;
		ECS::getInstance().addComponent<Transform>(player, playerTransform);
		ECS::getInstance().addComponent<Renderable>(player, Renderable(LevelGenerator::PlayerPath));
		ECS::getInstance().addComponent<CollidableBox>(player, playerBox);
		ECS::getInstance().addComponent<ScriptComponent>(player, ScriptComponent(LevelGenerator::PlayerScript));
		ScriptManager::GetInstance().createScriptController(
			(Paths::SCRIPTS_PATH / LevelGenerator::PlayerScript).string(), ECS::getInstance().getComponent<ScriptComponent>(player).scriptableObject, player
		);
		Application::GetCamera().setOwner(player);
		IVY_CORE_TRACE("Spawned Player. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))",
			ECS::getInstance().getComponent<Transform>(player).getEntityId(),
			ECS::getInstance().getComponent<Tag>(player).tag,
			ECS::getInstance().getComponent<Transform>(player).position.x,
			ECS::getInstance().getComponent<Transform>(player).position.y,
			ECS::getInstance().getComponent<Transform>(player).rotation,
			ECS::getInstance().getComponent<Transform>(player).scale.x,
			ECS::getInstance().getComponent<Transform>(player).scale.y);

		// Spawn Enemies
		auto& it = fittest.getDesignElements().begin();
		for (int x = 0; x < (int)xMax; x++)
		{
			for (int y = 0; y < (int)yMax; y++)
			{
				if (it != fittest.getDesignElements().begin() || it != fittest.getDesignElements().end())
				{
					DesignElement& levelElement = *it;
					ElementType type = levelElement.getElementType();
					levelElement.transform.position.x = (x * positionOffset) - (xMax * positionOffset) / 2;
					levelElement.transform.position.y = (y * positionOffset) - (yMax * positionOffset) / 2;
					if (it != fittest.getDesignElements().begin())
					{
						if (type == ElementType::TShaped)
						{
							collectable = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(collectable, Tag(std::string("Collectable-" + std::to_string(collectibleTagCounter++))));
							Transform collectTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 2), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox collectBox = CollidableBox(collectTransform.position, collectTransform.rotation, collectTransform.scale);
							collectBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(collectable, collectTransform);
							ECS::getInstance().addComponent<Renderable>(collectable, Renderable(LevelGenerator::CollectablePath));
							ECS::getInstance().addComponent<CollidableBox>(collectable, collectBox);
							ECS::getInstance().addComponent<ScriptComponent>(collectable, ScriptComponent(LevelGenerator::CollectableScript));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::CollectableScript).string(), ECS::getInstance().getComponent<ScriptComponent>(collectable).scriptableObject, collectable
							);
							IVY_CORE_TRACE("Spawned Collectable. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))",
								ECS::getInstance().getComponent<Transform>(collectable).getEntityId(),
								ECS::getInstance().getComponent<Tag>(collectable).tag,
								ECS::getInstance().getComponent<Transform>(collectable).position.x,
								ECS::getInstance().getComponent<Transform>(collectable).position.y,
								ECS::getInstance().getComponent<Transform>(collectable).rotation,
								ECS::getInstance().getComponent<Transform>(collectable).scale.x,
								ECS::getInstance().getComponent<Transform>(collectable).scale.y);
						}
						else if (type == ElementType::Hole)
						{
							collectable = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(collectable, Tag(std::string("Collectable-" + std::to_string(collectibleTagCounter++))));
							Transform collectTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 6), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox collectBox = CollidableBox(collectTransform.position, collectTransform.rotation, collectTransform.scale);
							collectBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(collectable, collectTransform);
							ECS::getInstance().addComponent<Renderable>(collectable, Renderable(LevelGenerator::CollectablePath));
							ECS::getInstance().addComponent<CollidableBox>(collectable, collectBox);
							ECS::getInstance().addComponent<ScriptComponent>(collectable, ScriptComponent(LevelGenerator::CollectableScript));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::CollectableScript).string(), ECS::getInstance().getComponent<ScriptComponent>(collectable).scriptableObject, collectable
							);
							IVY_CORE_TRACE("Spawned Collectable. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))",
								ECS::getInstance().getComponent<Transform>(collectable).getEntityId(),
								ECS::getInstance().getComponent<Tag>(collectable).tag,
								ECS::getInstance().getComponent<Transform>(collectable).position.x,
								ECS::getInstance().getComponent<Transform>(collectable).position.y,
								ECS::getInstance().getComponent<Transform>(collectable).rotation,
								ECS::getInstance().getComponent<Transform>(collectable).scale.x,
								ECS::getInstance().getComponent<Transform>(collectable).scale.y);
						}
						else if (type == ElementType::Pillar)
						{
							collectable = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(collectable, Tag(std::string("Collectable-" + std::to_string(collectibleTagCounter++))));
							Transform collectTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 5), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox collectBox = CollidableBox(collectTransform.position, collectTransform.rotation, collectTransform.scale);
							collectBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(collectable, collectTransform);
							ECS::getInstance().addComponent<Renderable>(collectable, Renderable(LevelGenerator::CollectablePath));
							ECS::getInstance().addComponent<CollidableBox>(collectable, collectBox);
							ECS::getInstance().addComponent<ScriptComponent>(collectable, ScriptComponent(LevelGenerator::CollectableScript));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::CollectableScript).string(), ECS::getInstance().getComponent<ScriptComponent>(collectable).scriptableObject, collectable
							);
							IVY_CORE_TRACE("Spawned Collectable. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))",
								ECS::getInstance().getComponent<Transform>(collectable).getEntityId(),
								ECS::getInstance().getComponent<Tag>(collectable).tag,
								ECS::getInstance().getComponent<Transform>(collectable).position.x,
								ECS::getInstance().getComponent<Transform>(collectable).position.y,
								ECS::getInstance().getComponent<Transform>(collectable).rotation,
								ECS::getInstance().getComponent<Transform>(collectable).scale.x,
								ECS::getInstance().getComponent<Transform>(collectable).scale.y);
						}
						else 
						{
							collectable = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(collectable, Tag(std::string("Collectable-" + std::to_string(collectibleTagCounter++))));
							Transform collectTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox collectBox = CollidableBox(collectTransform.position, collectTransform.rotation, collectTransform.scale);
							collectBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(collectable, collectTransform);
							ECS::getInstance().addComponent<Renderable>(collectable, Renderable(LevelGenerator::CollectablePath));
							ECS::getInstance().addComponent<CollidableBox>(collectable, collectBox);
							ECS::getInstance().addComponent<ScriptComponent>(collectable, ScriptComponent(LevelGenerator::CollectableScript));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::CollectableScript).string(), ECS::getInstance().getComponent<ScriptComponent>(collectable).scriptableObject, collectable
							);
							IVY_CORE_TRACE("Spawned Collectable. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))",
								ECS::getInstance().getComponent<Transform>(collectable).getEntityId(),
								ECS::getInstance().getComponent<Tag>(collectable).tag,
								ECS::getInstance().getComponent<Transform>(collectable).position.x,
								ECS::getInstance().getComponent<Transform>(collectable).position.y,
								ECS::getInstance().getComponent<Transform>(collectable).rotation,
								ECS::getInstance().getComponent<Transform>(collectable).scale.x,
								ECS::getInstance().getComponent<Transform>(collectable).scale.y);
						}
						
					}
					switch (type)
					{
					case ElementType::VerticalWall:
						IVY_CORE_TRACE("Adding VerticalWall Entities");
						// Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTilePos * 5), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolH).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
						break;
					case ElementType::HorizontalWall:
						IVY_CORE_TRACE("Adding HorizontalWall Entities");
						// Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x - halfTilePos, levelElement.transform.position.y - halfTilePos * 6), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolV));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolV).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
						break;
					case ElementType::Pillar:
						IVY_CORE_TRACE("Adding Pillar Entities");
						// Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x + 3 * halfTilePos, levelElement.transform.position.y + 5 * halfTilePos), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyGroundPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolH).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
						
						break;
					case ElementType::Hole:
						IVY_CORE_TRACE("Adding Hole Entities");
						// Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x - 6 * halfTilePos, levelElement.transform.position.y - 6 * halfTilePos), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyGroundPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolH).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
						break;
					case ElementType::RangedEnemy:
						IVY_CORE_TRACE("Adding RangedEnemy Entities");
						// Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x + halfTilePos * 2, levelElement.transform.position.y + halfTilePos * 6), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolH).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x + halfTilePos, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
						break;
					case ElementType::TShaped:
						IVY_CORE_TRACE("Adding TShaped Entities");
						// Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y - halfTilePos * 2), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyFlyPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolH).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
						break;
					case ElementType::ClosedRoom:
						IVY_CORE_TRACE("Adding ClosedRoom Entities");
						// Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyGroundPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolH));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolH).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
						break;
					case ElementType::MeleeEnemy:
						//IVY_CORE_TRACE("Adding MeleeEnemy Entities");
						//Enemies
						{
							enemy = ECS::getInstance().createEntity();
							ECS::getInstance().addComponent<Tag>(enemy, Tag(std::string("Enemy-" + std::to_string(enemyTagCounter++))));
							Transform enemyTransform = Transform(
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y), 0, glm::vec2(halfTileSize * 2, halfTileSize * 2)
							);
							CollidableBox enemyBox = CollidableBox(enemyTransform.position, enemyTransform.rotation, enemyTransform.scale);
							enemyBox.isTrigger = true;
							ECS::getInstance().addComponent<Transform>(enemy, enemyTransform);
							ECS::getInstance().addComponent<Renderable>(enemy, Renderable(LevelGenerator::EnemyGroundPath));
							ECS::getInstance().addComponent<CollidableBox>(enemy, enemyBox);
							ECS::getInstance().addComponent<ScriptComponent>(enemy, ScriptComponent(LevelGenerator::ScriptPatrolV));
							ScriptManager::GetInstance().createScriptController(
								(Paths::SCRIPTS_PATH / LevelGenerator::ScriptPatrolV).string(), ECS::getInstance().getComponent<ScriptComponent>(enemy).scriptableObject, enemy
							);
							IVY_CORE_TRACE("Spawned Enemy. Entity={0}, Tag={1}, Transform=(({2},{3}), {4}, ({5}, {6}))", enemy,
								ECS::getInstance().getComponent<Tag>(enemy).tag,
								enemyTransform.position.x, enemyTransform.position.y, enemyTransform.rotation, enemyTransform.scale.x, enemyTransform.scale.y);
						}
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
					ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::VerticalBorderPath));
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
					ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::HorizontalBorderPath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::HallwayPath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::VerticalWallPath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::HorizontalWallPath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::PillarPath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::HolePath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::RangedEnemyPath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::StdRoom1Path));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::StdRoom2Path));
						// Empty
						break;
					case ElementType::TShaped:
						IVY_CORE_TRACE("Adding TShaped, Type={0}", std::to_string(type));
						ECS::getInstance().addComponent<Tag>(entity, Tag(levelElement.tag));
						ECS::getInstance().addComponent<Transform>(entity, Transform(levelElement.transform));
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::TShapePath));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::ClosedRoomPath));
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
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTileSize * 7), 0, glm::vec2(halfTileSize * 6, halfTileSize));
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
						ECS::getInstance().addComponent<Renderable>(entity, Renderable(LevelGenerator::MeleeEnemyPath));
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
								glm::vec2(levelElement.transform.position.x, levelElement.transform.position.y + halfTileSize * 7), 0, glm::vec2(halfTileSize * 6, halfTileSize));
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
		LevelGenerator::IsGenerating = false;
	}

}