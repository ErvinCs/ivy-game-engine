#include "ivypch.h"
#include "Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "InputHandler.h"

namespace Ivy {

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		
		window->setCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		imGuiLayer = new ImGuiLayer();
		pushLayer(imGuiLayer);
	}


	Application::~Application()
	{
		//delete imGuiLayer;
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

		while (isRunning)
		{
			//memoryManager.run();
			//fileManager.run();
			//inputManager.run();
			//rendererManager.run();
			
			imGuiLayer->begin();
			for (SortingLayer* layer : layerStack)
				layer->imGuiRender();
			imGuiLayer->end();

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
		layer->attach();
	}

	void Application::onEvent(Event& event)
	{
		// TODO - Propagate event through layers (iterate from end to begin)
		//IVY_CORE_WARN("OnEvent: {0}", event.toString());
		//event();
		//event();	//TODO - call event in the update loop at some event processing stage, use EventHandles
		
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		isRunning = false;
		return true;
	}
}