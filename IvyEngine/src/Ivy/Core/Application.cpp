#include "ivypch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Logger.h"
#include "InputHandler.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/BaseRenderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../imgui/imgui.h"

namespace Ivy {

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;
		window = Window::Create();
		window->setCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		BaseRenderer::Init();

		imGuiLayer = new ImGuiLayer();
		pushLayer(imGuiLayer);
	}


	Application::~Application()
	{
		//delete imGuiLayer;
		BaseRenderer::Shutdown();
	}

	void Application::init()
	{
		memoryManager.init();
		fileManager.init();
		inputManager.init();
		rendererManager.init();
	}

	void Application::run()
	{

		while (isRunning)
		{
			//memoryManager.run();
			//fileManager.run();
			//inputManager.run();
			//rendererManager.run();

			float time = (float)glfwGetTime();
			Timestep ts = time - lastFrameTime;
			lastFrameTime = time;

			for (SortingLayer* layer : layerStack)
				layer->update(ts);

			imGuiLayer->begin();
			for (SortingLayer* layer : layerStack)
				layer->imGuiRender();
			imGuiLayer->end();

			window->update();
		}
	}

	void Application::shutdown()
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
		IVY_CORE_WARN("OnEvent: {0}", event.toString());
		//event();
		//TODO - call event in the update loop at some event processing stage, use EventHandles
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		isRunning = false;
		return true;
	}
}