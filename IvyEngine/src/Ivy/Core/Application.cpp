#include "ivypch.h"
#include "Application.h"

#include <glad/glad.h>

namespace Ivy {


	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());
		
		window->setCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
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

		Event e;
		//EventHandler eHandler = []() {
		//	std::cout << "e notified!";
		//};
		//e.addHandler(eHandler);
		//e();
		while (isRunning)
		{
			//memoryManager.run();
			//fileManager.run();
			//inputManager.run();
			//rendererManager.run();
			
			//TODO - for each layer call update()

			//glClearColor(1, 0, 1, 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			window->update();
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
		// TODO - Propagate event through layers (iterate from end to begin)
		//IVY_CORE_WARN("OnEvent: {0}", event.toString());
		event();
		//event();	//TODO - call event in the update loop at some event processing stage, use EventHandles
		
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		isRunning = false;
		return true;
	}
}