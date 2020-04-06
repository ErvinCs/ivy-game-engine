#pragma once

#include "../Core/SortingLayer.h"

namespace Ivy {
	class InspectorLayer : public SortingLayer
	{
	public:
		InspectorLayer() = default;
		~InspectorLayer() = default;

		virtual void imGuiRender() override;
	};
}