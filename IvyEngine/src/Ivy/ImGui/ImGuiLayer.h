#pragma once

#include "../Core/SortingLayer.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/WindowEvent.h"

namespace Ivy {

	/*
	 *
	 */
	class ImGuiLayer : public SortingLayer
	{
	public:
		/**
		 *
		 */
		ImGuiLayer();
		~ImGuiLayer();

		/**
		 *
		 */
		virtual void attach() override;
		
		/**
		 *
		 */
		virtual void detach() override;

		/**
		 *
		 */
		virtual void imGuiRender() override;

		/**
		 *
		 */
		void begin();

		/**
		 *
		 */
		void end();
	private:
	private:
		float time = 0.0;
	
	};

}