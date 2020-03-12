#pragma once


#include "Core.h"
#include "SortingLayerStack.h"
#include "../Windows/WindowsWindow.h"
#include "../Windows/WindowsInputHandler.h"
#include "String.h"

#include "../Events/KeyEvent.h"
#include "../Events/WindowEvent.h"
#include "../Events/MouseEvent.h"

#include "../Managers/FileManager.h"
#include "../Managers/MemoryManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/RendererManager.h"

#include "../ImGui/ImGuiLayer.h"

namespace Ivy {

	class Application 
	{
	private:
		static Application* instance;
		SortingLayerStack layerStack;
		std::unique_ptr<Window> window;
		bool isRunning = true;
		ImGuiLayer* imGuiLayer;
		float lastFrameTime = 0.0f;

	protected:
		//MemoryManager& memoryManager = MemoryManager::getInstance();
		//FileManager& fileManager = FileManager::getInstance();
		//InputManager& inputManager = InputManager::getInstance();
		//RendererManager& rendererManager = RendererManager::getInstance();

	public:
		inline static Application& getInstance()
		{
			return *instance;
		}

		Application();
		virtual ~Application();

		void init();
		void run();
		void shutdown();

		void pushLayer(SortingLayer* layer);
		void onEvent(Event& event);

		inline Window& getWindow() { return *window; }
		inline static Application& GetApplication() { return *instance; }
	private:
		bool onWindowClose(WindowCloseEvent& event);

	};

	// Defined in client
	Application* CreateApp();
}
