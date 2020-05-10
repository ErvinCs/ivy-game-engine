#include "ivypch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../imgui/imgui.h"

#include "Logger.h"
#include "InputHandler.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/BaseRenderer.h"
#include "../ECS/ECS.h"


namespace Ivy {

	Application* Application::instance = nullptr;

	OrthoCamera Application::camera = OrthoCamera(-12.8f, 12.8f, -6.4f, 6.4f);
	LevelGenerator Application::levelGenerator = LevelGenerator();

	Application::Application()
	{
		globalTime = 0;
		currTime = 0;
		lastFrameTime = 0;

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

		JSONManager::InitFunctions();
#ifdef _DEBUG
		imGuiLayer = new ImGuiLayer();
		inspectorLayer = new InspectorLayer();
		generationLayer = new GenerationLayer();

		pushLayer(imGuiLayer);
		pushLayer(inspectorLayer);
		pushLayer(generationLayer);
#endif
	}


	Application::~Application()
	{
#ifdef _DEBUG
		layerStack.pop(imGuiLayer);
		imGuiLayer = 0;
		layerStack.pop(inspectorLayer);
		inspectorLayer = 0;
		layerStack.pop(generationLayer);
		generationLayer = 0;
#endif
		BaseRenderer::Shutdown();
	}

	void Application::init()
	{
		//ECS::getInstance().loadEntities();
		ECS::getInstance().initSystems();
	}

	void Application::run()
	{
		while (isRunning)
		{
			if (!isPaused && !windowResized)
			{
				currTime = (float)glfwGetTime();
				globalTime = currTime - lastFrameTime;
				lastFrameTime = currTime;
			}
			else
			{
				currTime = (float)glfwGetTime();
				globalTime = 0;
				lastFrameTime = currTime;
				if (windowResized)
					windowResized = false;
			}
			

			ECS::getInstance().updateSystems(globalTime);

			for (SortingLayer* layer : layerStack)
				layer->update(globalTime);
#ifdef _DEBUG
			imGuiLayer->begin();
			for (SortingLayer* layer : layerStack)
				layer->imGuiRender();
			imGuiLayer->end();
#endif
			window->update();
		}
	}

	void Application::shutdown()
	{
		//ECS::getInstance().saveEntities();
		Renderer::Shutdown();
	}

	void Application::pushLayer(SortingLayer* layer)
	{
		this->layerStack.push(layer);
		layer->attach();
	}

	void Application::onEvent(Event& event)
	{
		switch (event.type)
		{
		case 1:	// Close
			this->isRunning = false;
			IVY_CORE_TRACE("Window Close Event");
			break;
		case 2:	// Resize
			currTime = (float)glfwGetTime();
			globalTime = 0;
			lastFrameTime = currTime;
			windowResized = true;
			IVY_CORE_TRACE("Window Resize Event");
			break;
		default:
			break;
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& ev)
	{
		isRunning = false;
		return true;
	}

	bool Application::onWindowResize(WindowResizeEvent& ev)
	{
		currTime = (float)glfwGetTime();
		globalTime = 0;
		lastFrameTime = currTime;
		return true;
	}
}