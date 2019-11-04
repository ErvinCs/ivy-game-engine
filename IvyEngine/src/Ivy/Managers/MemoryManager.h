#pragma once
#include "BaseManager.h"

namespace Ivy {

	class MemoryManager : public BaseManager
	{
	public:
		MemoryManager() {}
		~MemoryManager() {}

	protected:
		void initHook();
		void updateHook();
		void shutdownHook();

	};

}