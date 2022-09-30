#pragma once

#include "../Core/SortingLayer.h"

namespace Ivy {
	/**
	 * Creates a new layer containing the ImGUI for manipulation the PCG algorithm parameters.
	 * @see SortingLayer
	 */
	class GenerationLayer : public SortingLayer
	{
	public:
		GenerationLayer() = default;

		~GenerationLayer() = default;

		/**
		 * Renders the ImGUI for the `GenerationLayer`.
		 * Called every frame.
		 */
		virtual void imGuiRender() override;
	};
}