#pragma once

#include "Core.h"

namespace Ivy {

	class IVY_API Application 
	{
	
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	// Defined in client
	Application* CreateApplication();
}
