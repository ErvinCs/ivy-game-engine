#include "ivypch.h"
#include "SortingLayer.h"

namespace Ivy {
	SortingLayer::SortingLayer(const std::string& name) : layerName(name)
	{
		this->layerRank = 0;
		IVY_CORE_TRACE("SortingLayer: Constructing Layer: name={0}, rank={1}", layerName, layerRank);
	}

	SortingLayer::SortingLayer(const std::string& name, const unsigned int& rank) : layerName(name), layerRank(rank)
	{
		IVY_CORE_TRACE("SortingLayer: Constructing Layer: name={0}, rank={1}", layerName, layerRank);
	}

	SortingLayer::~SortingLayer()
	{
		IVY_CORE_TRACE("SortingLayer: Destroying Layer: name={0}, rank={1}", layerName, layerRank);
	}
}