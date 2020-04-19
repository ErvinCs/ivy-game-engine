#pragma once

#include "FI2Pop.h"

namespace Ivy
{

	class LevelGenerator
	{
	private:
		FI2Pop generator;
		Population finalPopulation;
		Individual fittest;
		Graph graph;
		const float positionOffset = 8.0f;
		const float wallOfsset = 3.5f;
	public:
		LevelGenerator();
		
		void run();

		void exportLevelSet() {}
	};

}