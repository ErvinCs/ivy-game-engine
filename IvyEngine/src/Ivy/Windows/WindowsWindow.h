#pragma once

#include "../Core/Window.h"

namespace Ivy {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		~WindowsWindow();

		inline unsigned int getHeight() const { return 0; } //height 
		inline unsigned int getWidth() const { return 0; } //width } 
		
	private:
		WindowProperties properties;
	};

}