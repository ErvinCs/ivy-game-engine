#pragma once

#include <Windows.h>

#include "Core.h"
#include "SortingLayerStack.h"
#include "../Windows/WindowsWindow.h"
#include "../Windows/WindowsInputHandler.h"
#include "String.h"

#include "../Events/KeyEvent.h"
#include "../Events/WindowEvent.h"
#include "../Events/MouseEvent.h"

#include "../ImGui/ImGuiLayer.h"
#include "../ImGui/InspectorLayer.h"
#include "../ImGui/GenerationLayer.h"
#include "../Scripting/ScriptManager.h"

#include "../Renderer/OrthoCamera.h"
#include "../ECS/JSONManager.h"
#include "../PCG/LevelGenerator.h"

namespace Ivy {
	class Application 
	{
	private:
		static Application* instance;
		static OrthoCamera camera;
		static LevelGenerator levelGenerator;
		SortingLayerStack layerStack;
		std::unique_ptr<Window> window;
		ScriptManager* scriptManager;
#ifdef _DEBUG
		ImGuiLayer* imGuiLayer;
		InspectorLayer* inspectorLayer;
		GenerationLayer* generationLayer;
#endif	
		bool windowResized = false;
	public:
		bool isRunning = true;
		bool isPaused = false;
		float globalTime;
		float currTime;
		float lastFrameTime;

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
		inline static OrthoCamera& GetCamera() { return camera; }
		inline static LevelGenerator& GetLevelGenerator() { return levelGenerator; }
	private:
		bool onWindowClose(WindowCloseEvent& ev);
		bool onWindowResize(WindowResizeEvent& ev);

	};

	// Defined in client
	Application* CreateApp();
}
