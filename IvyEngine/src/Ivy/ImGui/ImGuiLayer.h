#pragma once

#include "../Core/SortingLayer.h""
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/WindowEvent.h"


namespace Ivy {

	class ImGuiLayer : public SortingLayer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void attach() override;
		virtual void detach() override;
		virtual void imGuiRender() override;

		void begin();
		void end();
	private:
		// Returns true if event was handled (consumed); false otherwise
		//bool onKeyDownEvent(KeyDownEvent& event);
		//bool onKeyUpEvent(KeyUpEvent& event);
		//bool onMouseButtonDownEvent(MouseButtonDownEvent& event);
		//bool onMouseButtonUpEvent(MouseButtonUpEvent& event);
		//bool onMouseMoveEvent(MouseMoveEvent& event);
		//bool onMouseScrollEvent(MouseScrollEvent& event);
		//bool onWindowReseizeEvent(WindowResizeEvent& event);
	private:
		float time = 0.0;
	
	};

}