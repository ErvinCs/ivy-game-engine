#pragma once

#include "FI2Pop.h"

namespace Ivy
{
	/**
	 * The LevelGenerator runs the generation algorithm and spawns all the entities
	 *  according to the values stored in the resulting genotype.
	 * @see FI2Pop
	 */
	class LevelGenerator
	{
	private:
		// The algorithm used to generate levels
		FI2Pop generator;

		Individual fittest;
		Population finalPopulation;

		// The distance between the centers of every room
		const float positionOffset = 8.0f;
		// The distance of the walls from the center of the rooms situated at the map edges
		const float wallOfsset = 4.5f;
		// Half the size of a tile. Used to determine Transform and Collidable sizes for an Entity.
		const float halfTileSize = 0.49f;
		// Half the measure used for position. Used to determine Transform position for an Entity
		const float halfTilePos = 0.5f;
	public:
		static bool AlwaysLoad;
		static int AlwaysLoadFittest;
		static std::string HorizontalBorderPath;
		static std::string VerticalBorderPath;
		static std::string ClosedRoomPath;
		static std::string EnemyFlyPath;
		static std::string EnemyGroundPath;
		static std::string HallwayPath;
		static std::string HolePath;
		static std::string HorizontalWallPath;
		static std::string VerticalWallPath;
		static std::string PillarPath;
		static std::string MeleeEnemyPath;
		static std::string RangedEnemyPath;
		static std::string StdRoom1Path;
		static std::string StdRoom2Path;
		static std::string TShapePath;
		static std::string ScriptPatrolV;
		static std::string ScriptPatrolH;	
		static std::string LevelGenerator::PlayerScript;
		static std::string LevelGenerator::PlayerPath;
		static std::string CollectablePath;
		static std::string CollectableScript;
		static bool IsGenerating;

		/**
		 * Default constructor. Intializes the level generator algorithm
		 */
		LevelGenerator();
		
		/**
		 * Runs the generation algorithm.
		 * Once the algorithm finishes it spawns all the game Entities and attaches corresponding components
		 * @see FI2Pop
		 */
		void run();

		/**
		 * Clears the populations maintained by the algorithm
		 */
		void clearPopulations();

		/**
		 * @returns Individual having the highest fitness in the feaisble population. 
		 *  If feasible individuals do not exist then 
		 *  it returns the most fit infeaisble Individual
		 */
		inline Individual getFittest() { return this->fittest; }
	};
}