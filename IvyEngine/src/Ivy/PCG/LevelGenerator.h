#pragma once

#include "FI2Pop.h"

namespace Ivy
{

	class LevelGenerator
	{
	private:
		FI2Pop generator;
	public:
		LevelGenerator(const FI2Pop& generator);
		
		void init();
		void run();

		void exportLevelSet();
	};

}