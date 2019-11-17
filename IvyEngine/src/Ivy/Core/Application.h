#pragma once

//#include <GLFW/glfw3.h>

#include "Core.h"
#include "SortingLayerStack.h"
#include "../Windows/WindowsWindow.h"
#include "String.h"
#include "Logger.h"

#include "../Events/KeyEvent.h"
#include "../Events/WindowEvent.h"
#include "../Events/MouseEvent.h"

#include "../Managers/FileManager.h"
#include "../Managers/MemoryManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/RendererManager.h"

namespace Ivy {

	class Application 
	{
	private:
		static Application* instance;
		SortingLayerStack layerStack;
		std::unique_ptr<Window> window;
		bool isRunning = true;

	protected:
		MemoryManager& memoryManager = MemoryManager::getInstance();
		FileManager& fileManager = FileManager::getInstance();
		InputManager& inputManager = InputManager::getInstance();
		RendererManager& rendererManager = RendererManager::getInstance();

	public:
		Application();
		virtual ~Application();

		void Init();
		void Run();
		void Shutdown();

		void pushLayer(SortingLayer* layer);
		void onEvent(Event& event);

		inline Window& getWindow() { return *window; }
		inline static Application& getApplication() { return *instance; }
	private:
		bool onWindowClose(WindowCloseEvent& event);

	};

	// Defined in client
	Application* CreateApp();
}
