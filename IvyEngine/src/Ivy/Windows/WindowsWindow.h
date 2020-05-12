#pragma once

#include "../glfw/include/GLFW/glfw3.h"
#include "../Renderer/Context.h"

#include "../Core/Logger.h"
#include "../Core/Window.h"
#include "../Events/WindowEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"


namespace Ivy 
{
	/**
	 * Implementation of Window for Windows.
	 * @see: Window
	 */
	class WindowsWindow : public Window
	{
	public:
		// Initializes the window by calling `void init()`
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		/**
		 * Update the window. Poll input envents and swap buffers.
		 */
		void update() override;

		// @returns int The window height
		inline unsigned int getHeight() const override { return properties.wProps.height; }
		// @returns int The window width
		inline unsigned int getWidth() const override { return properties.wProps.width; }
		// @return GLFWwindow* A window handle to a glfw window
		inline virtual void* getNativeWindow() const override { return window; }
		
		/**
		 * Set a callack function on `properties`
		 * @param Func Callback invoked immediatly after a handle is notified by the occurence of an Event
		 */
		void setCallback(const Func& callback) override
		{
			properties.callback = callback;
		}

	private:
		/**
		 * Encapsulates WindowProperties and a function callback `void(Event& e)` aliased as `Func`.
		 * Invoked immediatly after a handle is notified by the occurence of an Event.
		 */
		struct WindowPropertiesUserData
		{
			WindowProperties wProps;
			Func callback;
		};

		// Holds the window properties and the event callback
		WindowPropertiesUserData properties;
		// Encapsulates a glfw window and a glfw context
		GLFWwindow* window;
		// Points to the render context. @see: Context
		std::unique_ptr<Context> context;

		/**
		 * Creates a window and initilizes it with the passed `properties`. Calls `glfwInit()`.
		 * Creates WindowEvents, KeyEvents, MouseEvents as callback functions.
		 * @param properties Encapsulates the properties of a Window instance
		 */
		virtual void init(const WindowProperties& properties);
		// Destroys the window by calling `glfwDestroyWindow`
		virtual void shutdown();
	};

}