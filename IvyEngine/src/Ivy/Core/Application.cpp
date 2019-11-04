#include "ivypch.h"
#include "Application.h"

namespace Ivy {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Init()
	{
		memoryManager.init();
		fileManager.init();
	}

	void Application::Run()
	{
		while (true);
		{
			memoryManager.run();
			fileManager.run();
		}
	}

	void Application::Shutdown()
	{
		fileManager.shutdown();
		memoryManager.shutdown();
	}

}