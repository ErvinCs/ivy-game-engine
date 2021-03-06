#include "ivypch.h"
#include "SortingLayerStack.h"

namespace Ivy {

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
			IVY_CORE_INFO("SortingLayerStack: Popping Layer");
		}
		else
		{
			throw new LayerException("Attempted to pop Layer, but Layer was not found!");
		}
	}

	void SortingLayerStack::push(SortingLayer* layer)
	{
		this->layers.push_back(layer);
		IVY_CORE_INFO("SortingLayerStack: Pushing Layer");
	}

}