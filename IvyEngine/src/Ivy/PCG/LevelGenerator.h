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
	public:
		LevelGenerator() = default;
		LevelGenerator(const FI2Pop& generator);
		
		void run();

		void exportLevelSet() {}
	};

}