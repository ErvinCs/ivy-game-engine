#pragma once

#include "Core.h"
#include "../Managers/FileManager.h"
#include "../Managers/MemoryManager.h"

namespace Ivy {

	class Application 
	{
	protected:
		FileManager fileManager;
		MemoryManager memoryManager;

	public:
		Application();
		virtual ~Application();

		void Init();
		void Run();
		void Shutdown();

	};

	// Defined in client
	Application* CreateApplication();
}
