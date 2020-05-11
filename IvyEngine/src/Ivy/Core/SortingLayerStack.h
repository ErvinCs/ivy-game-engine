#pragma once

#include "SortingLayer.h"
#include "../Exceptions/LayerException.h"
#include "Logger.h"
#include <vector>

namespace Ivy {
	/*
	 *
	 */
	class SortingLayerStack
	{
	public:
		SortingLayerStack();
		~SortingLayerStack();

		void push(SortingLayer* layer);
		void pop(SortingLayer* layer);

		std::vector<SortingLayer*>::iterator begin() { return layers.begin(); }
		std::vector<SortingLayer*>::iterator end() { return layers.end(); }
	private:
		std::vector<SortingLayer*> layers;
	};

}