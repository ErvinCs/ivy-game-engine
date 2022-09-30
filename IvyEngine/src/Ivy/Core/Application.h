#pragma once

#include <Windows.h>

#include "Core.h"
#include "SortingLayerStack.h"
#include "../Windows/WindowsWindow.h"
#include "../Windows/WindowsInputHandler.h"

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
	/**
	 * The base class for Ivy Applications.
	 * Initializes all subsystems and contains the main engine loop.
	 * Measures time, provides access to the layer stack and responds to events.
	 */
	class Application 
	{
	private:
		// Singular application instance
		static Application* Instance;
		// Singular camera instance
		static OrthoCamera Camera;
		// Singulare level generator instance
		static LevelGenerator LevelGen;

		// True while resizing the window
		bool windowResized = false;

		// Stack of layers
		SortingLayerStack layerStack;
		// Points to the singular script manager instance
		ScriptManager* scriptManager;
		// Points to a window depending on the target platform
		std::unique_ptr<Window> window;
#ifdef _DEBUG
		ImGuiLayer* imGuiLayer;
		InspectorLayer* inspectorLayer;
		GenerationLayer* generationLayer;
#endif	
	public:
		// True while the application is running
		bool isRunning = true;
		// True while the application is paused
		bool isPaused = false;
		// Used to measure application time
		float globalTime, currTime, lastFrameTime;
	
		/**
		 * Constructor called on creating the Application instance.
		 */
		Application();

		/**
		 * On destroying the application the renderer is shut down.
		 * In Debug the GUI layers are destroyed.
		 */
		virtual ~Application();

		/**
		 * Initializes the application.
		 * Starts time measurement, creates a Window, intializes the Renderer, intializes the ScriptManager, initializes the JSON conversion function pointers.
		 * In Debug it pushes the GUI layers: InspectorLayer, GenerationLayer, ImGuiLayer.
		 */
		void init();
		void run();
		void shutdown();

		/**
		 * Push a layer onto the SortingLayerStack.
		 * @param layer SortingLayer* pointer to the layer to be pushed.
		 */
		void pushLayer(SortingLayer* layer);

		/**
		 * Specifies behavior on receiving an Event.
		 * @param event Event the received Event
		 */
		void onEvent(Event& event);

		/**
		 * @returns the handle to the window in which the application is runnning
		 */
		inline Window& getWindow() { return *window; }

		/**
		 * @returns the static Application instance.
		 */
		inline static Application& GetInstance() { return *Instance; }

		/**
		 * @returns the static OrthoCamera instance.
		 */
		inline static OrthoCamera& GetCamera() { return Camera; }

		/**
		 * @returns the static LevelGenerator instance.
		 */
		inline static LevelGenerator& GetLevelGenerator() { return LevelGen; }
	private:
		/**
		 * Responds to closing the application window.
		 * Shuts down the application.
		 * @param ev WindowCloseEvent created on closing the window.
		 * @returns true on closing the window.
		 */
		bool onWindowClose(WindowCloseEvent& ev);

		/**
		 * Responds to resizing the application window.
		 * Pauses the time while window is being resized.
		 * @param ev WindowResizeEvent created on resizing the window
		 * @returns true on resizing the window
		 */
		bool onWindowResize(WindowResizeEvent& ev);
	};

	// Defined in the client Application. Returns a new Application instance.
	Application* CreateApp();
}
