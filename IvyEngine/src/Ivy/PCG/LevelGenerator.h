#pragma once

#include "FI2Pop.h"

namespace Ivy
{

	class LevelGenerator
	{
	private:
		FI2Pop generator;
	public:
		LevelGenerator();
		
		void init();
		void run();

		void exportLevelSet();
	};

}