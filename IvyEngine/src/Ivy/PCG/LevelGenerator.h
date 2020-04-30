#pragma once

#include "FI2Pop.h"

namespace Ivy
{

	class LevelGenerator
	{
	private:
		FI2Pop generator;
		Individual fittest;
		Population finalPopulation;
		const float positionOffset = 8.0f;
		const float wallOfsset = 4.5f;
		const float halfTileSize = 0.49f;
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
		LevelGenerator();
		
		void run();
		inline Individual getFittest() { return this->fittest; }
	};

}