#pragma once
#include "Manager.h"

namespace Ivy {

	class MemoryManager : public Manager
	{
	public:
		~MemoryManager() = default;

		static MemoryManager& getInstance()
		{
			static MemoryManager instance{};
			return instance;
		}
	protected:
		void initHook();
		void updateHook();
		void shutdownHook();

		MemoryManager() {}
		MemoryManager(const MemoryManager&) = delete;
		MemoryManager& operator=(const MemoryManager&) = delete;

	};

}