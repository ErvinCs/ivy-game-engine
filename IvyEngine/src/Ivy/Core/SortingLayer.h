#pragma once

#include "../Events/Event.h"
#include "Timestep.h"

#include <string>

namespace Ivy {

	class SortingLayer
	{
	public:
		SortingLayer(const std::string& name = "Layer");
		SortingLayer(const std::string& name, const unsigned int& rank);
		~SortingLayer() = default;

		virtual void attach() {}
		virtual void detach() {}
		virtual void update(Timestep ts) {}
		virtual void onEvent(Event& event) {}
		virtual void imGuiRender() {}

	private:
		std::string layerName;
		unsigned int layerRank;
	};

}