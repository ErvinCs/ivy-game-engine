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
		//globalTime = new Timestep(0);
		globalTime = 0;

		int success;
		instance = this;
		window = Window::Create();
		window->setCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		BaseRenderer::Init();

		this->scriptManager = &ScriptManager::GetInstance();
		success = scriptManager->init();
		if (success < 0)
		{
			IVY_CORE_ERROR("Could not initialize script manager!");
			delete scriptManager;
		}
		if (scriptManager->getHasCompileErrors())
		{
			IVY_CORE_ERROR("Compile errors on script load!");
		}

		imGuiLayer = new ImGuiLayer();
		pushLayer(imGuiLayer);
	}


	Application::~Application()
	{
		delete imGuiLayer;
		BaseRenderer::Shutdown();
		if (scriptManager)
		{
			delete scriptManager;
			scriptManager = 0;
		}
	}

	void Application::init()
	{

	}

	void Application::run()
	{

		while (isRunning)
		{

			float time = (float)glfwGetTime();
			globalTime = time - lastFrameTime;
			lastFrameTime = time;

			for (SortingLayer* layer : layerStack)
				layer->update(globalTime);

			imGuiLayer->begin();
			for (SortingLayer* layer : layerStack)
				layer->imGuiRender();
			imGuiLayer->end();

			window->update();
		}
	}

	void Application::shutdown()
	{
		//delete globalTime;
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
		//TODO - call event in the update loop at some event processing stage, use EventHandles
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		isRunning = false;
		return true;
	}
}