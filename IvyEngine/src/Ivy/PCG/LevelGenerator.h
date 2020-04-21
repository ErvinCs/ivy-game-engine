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
		const float halfTileSize = 0.33f;
	public:
		LevelGenerator();
		
		void run();
	};

}