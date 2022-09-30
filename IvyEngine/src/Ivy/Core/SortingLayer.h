#pragma once

#include "../Events/Event.h"
#include "Timestep.h"
#include "Logger.h"

#include <string>

namespace Ivy {

	/**
	 * Logically separate game objects.
	 * Provides methods to update game objects, react to events and render ImGui GUIs.
	 * Also see: LayerStack
	 */
	class SortingLayer
	{
	public:
		/**
		 * Base constructor. Sets the `layerRank` to 0.
		 * @param name string representing the name of the layer; "Layer" by default
		 */
		SortingLayer(const std::string& name = "Layer");

		/**
		 * Constructor that requires a the layer name and the layer rank
		 * @param name string representing the name of the layer
		 * @param rank representing 
		 */
		SortingLayer(const std::string& name, const unsigned int& rank);

		~SortingLayer();

		/**
		 * Define actions to occur on attaching the layer.
		 */
		virtual void attach() {}

		/**
		 * Define actions to occur on dettaching the layer.
		 */
		virtual void detach() {}

		/**
		 * Layer specific update actions. 
		 * Called by the application in the update phase.
		 * @param ts Timestep used to steady the framerate
		 */
		virtual void update(Timestep ts) {}

		/**
		 * Layer specific event handling.
		 * @param event Event that was raised by other subsystems and requires handling
		 */
		virtual void onEvent(Event& event) {}

		/**
		 * This method is used to define the ImGui GUI elements of the layer.
		 */
		virtual void imGuiRender() {}
	private:
		// The name of the layer
		std::string layerName;
		// The importance of the layer. Equivalent to its rank in the layer stack.
		unsigned int layerRank;
	};
}