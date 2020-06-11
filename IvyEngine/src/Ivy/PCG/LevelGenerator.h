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
		static bool alwaysLoad;
		static int alwaysLoadFittest;
		static std::string horizontalBorderPath;
		static std::string verticalBorderPath;
		static std::string closedRoomPath;
		static std::string enemyFlyPath;
		static std::string enemyGroundPath;
		static std::string hallwayPath;
		static std::string holePath;
		static std::string horizontalWallPath;
		static std::string verticalWallPath;
		static std::string pillarPath;
		static std::string meleeEnemyPath;
		static std::string rangedEnemyPath;
		static std::string stdRoom1Path;
		static std::string stdRoom2Path;
		static std::string tShapePath;
		static std::string scriptPatrolV;
		static std::string scriptPatrolH;	
		static std::string LevelGenerator::playerScript;
		static std::string LevelGenerator::playerPath;
		static std::string collectablePath;
		static std::string collectableScript;
		static bool isGenerating;

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