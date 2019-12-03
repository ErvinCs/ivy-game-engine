#pragma once

#include "../glfw/include/GLFW/glfw3.h"
#include "../Renderer/Context.h"

#include "../Core/Logger.h"
#include "../Core/Window.h"
#include "../Events/WindowEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"


namespace Ivy {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void update() override;

		inline unsigned int getHeight() const override { return properties.wProps.height; }
		inline unsigned int getWidth() const override { return properties.wProps.width; }
		inline virtual void* GetNativeWindow() const override { return window; }
		
		void setCallback(const Func& callback) override
		{
			properties.callback = callback;
		}



	private:
		struct WindowPropertiesUserData
		{
			WindowProperties wProps;
			Func callback;
		};

		WindowPropertiesUserData properties;
		GLFWwindow* window;
		Context* context;

		virtual void init(const WindowProperties& properties);
		virtual void shutdown();
	};

}