#include "ivypch.h"
#include "SortingLayerStack.h"

namespace Ivy {

	SortingLayerStack::SortingLayerStack()
	{
	}


	SortingLayerStack::~SortingLayerStack()
	{
		for (SortingLayer* layer : this->layers)
		{
			delete layer;
		}
	}

	void SortingLayerStack::pop(SortingLayer* layer)
	{
		auto searched = std::find(layers.begin(), layers.end(), layer);
		if (searched != layers.end())
		{
			layers.erase(searched);
		}
		else
		{
			throw new LayerException("Sorting layer to delete was not found!");
		}
	}

	void SortingLayerStack::push(SortingLayer* layer)
	{
		this->layers.push_back(layer);
	}

}