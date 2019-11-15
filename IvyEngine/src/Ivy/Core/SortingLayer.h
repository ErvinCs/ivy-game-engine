#pragma once

namespace Ivy {

	class SortingLayer
	{
	public:
		SortingLayer();
		SortingLayer(const std::string& name);
		SortingLayer(const std::string& name, const unsigned int& rank);
		~SortingLayer() = default;

	private:
		std::string layerName;
		unsigned int layerRank;
	};

}