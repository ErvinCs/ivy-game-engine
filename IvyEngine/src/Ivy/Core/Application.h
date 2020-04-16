#pragma once

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
#include "../Scripting/ScriptManager.h"

#include "../Renderer/OrthoCamera.h"
#include "../ECS/JSONManager.h"

namespace Ivy {

	

	class Application 
	{
	private:
		static Application* instance;
		static OrthoCamera camera;
		SortingLayerStack layerStack;
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		InspectorLayer* inspectorLayer;
		float lastFrameTime = 0.0f;
		ScriptManager* scriptManager;

	public:
		bool isRunning = true;
		float globalTime;

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
	private:
		bool onWindowClose(WindowCloseEvent& event);

	};

	// Defined in client
	Application* CreateApp();
}
