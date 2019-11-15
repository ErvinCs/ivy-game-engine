#include "ivypch.h"

#include "../Events/KeyEvent.h"
#include "String.h"
#include "Application.h"


namespace Ivy {


	Application::Application()
	{
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());

		//TODO: Create a layer & push it
	}


	Application::~Application()
	{
	}

	void Application::Init()
	{
		memoryManager.init();
		fileManager.init();
		inputManager.init();
		rendererManager.init();
	}

	void Application::Run()
	{
		Event myEvent{};
		EventHandler handler = []() {
			std::cout << "Test1: Event notification \t";
		};
		myEvent.addHandler(handler);
		KeyPressedEvent keyEvent{ 65, 1 };
		EventHandler keyA = []() {
			String string = String("Test2: KeyPressedEvent notification");
			std::cout << string;
		};
		myEvent.addHandler(keyA);
		myEvent();

		while (true);
		{
			memoryManager.run();
			fileManager.run();
			inputManager.run();
			rendererManager.run();
		}
	}

	void Application::Shutdown()
	{
		rendererManager.shutdown();
		inputManager.shutdown();
		fileManager.shutdown();
		memoryManager.shutdown();
	}

	void Application::pushLayer(SortingLayer* layer)
	{
		this->layerStack.push(layer);
	}

	void Application::onEvent(Event& event)
	{

	}
}