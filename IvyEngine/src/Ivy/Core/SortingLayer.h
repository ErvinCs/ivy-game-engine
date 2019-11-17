#pragma once

//#include "../Events/Event.h"

#include <string>

namespace Ivy {

	class SortingLayer
	{
	public:
		SortingLayer();
		SortingLayer(const std::string& name);
		SortingLayer(const std::string& name, const unsigned int& rank);
		~SortingLayer() = default;

		virtual void attach() {}
		virtual void detach() {}
		virtual void update() {}
		//virtual void onEvent(Event& event);

	private:
		std::string layerName;
		unsigned int layerRank;
	};

}