#include "ivypch.h"
#include "SortingLayer.h"

namespace Ivy {


	SortingLayer::SortingLayer(const std::string& name) : layerName(name)
	{
		this->layerRank = 0;
	}

	SortingLayer::SortingLayer(const std::string& name, const unsigned int& rank) : layerName(name), layerRank(rank)
	{
	}

}