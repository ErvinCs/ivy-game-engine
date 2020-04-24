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

		imGuiLayer = new ImGuiLayer();
		inspectorLayer = new InspectorLayer();
		generationLayer = new GenerationLayer();
		pushLayer(imGuiLayer);
		pushLayer(inspectorLayer);
		pushLayer(generationLayer);
	}


	Application::~Application()
	{
		delete imGuiLayer;
		delete inspectorLayer;
		delete generationLayer;
		BaseRenderer::Shutdown();
		if (scriptManager)
		{
			delete scriptManager;
			scriptManager = 0;
		}
	}

	void Application::init()
	{
		ECS::getInstance().loadEntities();
		ECS::getInstance().initSystems();
	}

	void Application::run()
	{
		//TODO - Generation should happen in IvyApplication. ImGui is only for tweaking
		//IVY_CORE_INFO("Starting generation");
		//levelGenerator.run();
		//IVY_CORE_INFO("Ending generation");
		while (isRunning)
		{

			float time = (float)glfwGetTime();
			globalTime = time - lastFrameTime;
			lastFrameTime = time;

			ECS::getInstance().updateSystems(globalTime);

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
		ECS::getInstance().saveEntities();
		Renderer::Shutdown();
	}

	void Application::pushLayer(SortingLayer* layer)
	{
		this->layerStack.push(layer);
		layer->attach();
	}

	void Application::onEvent(Event& event)
	{
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		isRunning = false;
		return true;
	}
}