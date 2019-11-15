#include "ivypch.h"
#include "SortingLayer.h"

namespace Ivy {

	SortingLayer::SortingLayer()
	{
		this->layerName = "";
		this->layerRank = -1;
	}


	SortingLayer::SortingLayer(const std::string& name)
	{
		this->layerName = name;
		this->layerRank = -1;
	}

	SortingLayer::SortingLayer(const std::string& name, const unsigned int& rank)
	{
		this->layerName = name;
		this->layerRank = rank;
	}

}