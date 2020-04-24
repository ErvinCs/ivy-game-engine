#pragma once

#include "../Core/SortingLayer.h"

namespace Ivy
{

	class GenerationLayer : public SortingLayer
	{
	public:
		GenerationLayer() = default;
		~GenerationLayer() = default;

		virtual void imGuiRender() override;
	};

}