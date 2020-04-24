#pragma once

#include "FI2Pop.h"

namespace Ivy
{

	class LevelGenerator
	{
	private:
		FI2Pop generator;
		Individual fittest;
		const float positionOffset = 8.0f;
		const float wallOfsset = 4.5f;
		const float halfTileSize = 0.49f;
		const float halfTilePos = 0.5f;
	public:
		static bool alwaysLoadFittest;
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
		static bool isGenerating;
		LevelGenerator();
		
		void run();
	};

}