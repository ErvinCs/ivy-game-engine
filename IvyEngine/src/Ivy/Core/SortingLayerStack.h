#pragma once

#include "SortingLayer.h"
#include "../Exceptions/LayerException.h"
#include "Logger.h"
#include <vector>

namespace Ivy {
	/**
	 * Aggregates Layers and provides iteration mechanisms.
	 * Used by the application to update each layer in a well defined order.
	 * Also see: Layer
	 */
	class SortingLayerStack
	{
	public:
		// Base constructor
		SortingLayerStack() {}
		// Base destructor. Free the layers in the layer stack.
		~SortingLayerStack();

		/**
		 * Push a layer on top of the layer stack
		 * @param layer Layer to be pushed
		 */
		void push(SortingLayer* layer);

		/**
		 * Pop a specific layer from the layer stack
		 * @param layer Layer to pe popped
		 */
		void pop(SortingLayer* layer);

		std::vector<SortingLayer*>::iterator begin() { return layers.begin(); }
		std::vector<SortingLayer*>::iterator end() { return layers.end(); }
	private:
		// Aggregation of Layer pointers.
		// Using pointers in order to allow iterating over instances of derived classes of Layer
		std::vector<SortingLayer*> layers;
	};

}