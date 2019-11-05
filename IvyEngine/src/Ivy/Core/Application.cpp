#include "ivypch.h"

#include "../Events/KeyEvent.h"
#include "String.h"
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
		Event myEvent{};
		EventHandler handler = []() {
			std::cout << "handler notification \t";
		};
		myEvent.addHandler(handler);

		KeyPressedEvent keyEvent{ 65, 1 };
		EventHandler keyA = []() {
			String string = String("KeyPressedEvent");
			std::cout << string;
		};
		myEvent.addHandler(keyA);
		
		myEvent();


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