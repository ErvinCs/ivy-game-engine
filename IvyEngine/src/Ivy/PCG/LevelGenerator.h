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
	public:
		LevelGenerator();
		
		void run();
	};

}