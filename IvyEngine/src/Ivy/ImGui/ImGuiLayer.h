#pragma once

#include "../Core/SortingLayer.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/WindowEvent.h"

namespace Ivy {
	/**
	 * The ImGuiLayer is in charge of starting and ending frames related to GUI rendering,
	 *  as well as setting the default options for any other ImGui layer.
	 * Note that each ImGui layer can define addition options.
	 * It also provides access to the demo window which provides examples for all common widgets.
	 */
	class ImGuiLayer : public SortingLayer
	{
	public:
		/**
		 * Sets the layer name and loads the required GLAD functions.
		 */
		ImGuiLayer();
		~ImGuiLayer();

		/**
		 * Create the ImGUI render context and intialize its configuration.
		 */
		virtual void attach() override;
		
		/** 
		 * Destroy the ImGUI render context.
		 */
		virtual void detach() override;

		/**
		 * Renders the ImGUI Demo which provides examples for all common widgets.
		 */
		virtual void imGuiRender() override;

		/**
		 * Begin a new ImGui frame.
		 */
		void begin();

		/**
		 * Render the frame draw data and set the current context.
		 */
		void end();
	private:
		// Used to maintain the framerate.
		float time = 0.0;
	};
}