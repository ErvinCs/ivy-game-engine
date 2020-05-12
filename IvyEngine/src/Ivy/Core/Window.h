#pragma once

#include <string>
#include "../Events/Event.h"

namespace Ivy {
	/**
	 * Encapsulates the properties of a Window instance.
	 * Stores the dimensions and name of the window.
	 */
	struct WindowProperties
	{
		std::string name;
		unsigned int width;
		unsigned int height;

		/**
		 * Base constructor.
		 * Creates a window with 1280x720 resolution.
		 * @param name String representing the name of the window; "Ivy" by default
		 */
		WindowProperties(const std::string& name = "Ivy",
			unsigned int width = 1280,
			unsigned int height = 720)
			: name(name), width(width), height(height)
		{}
	};

	/**
	 * Abstract class representing a window handle.
	 * Children are required to implement the methods
	 *  update, setCallback, getHeight, getWidth, getNativeWindow
	 */
	class Window
	{
	public:
		/** A Func equivalent to the `void onEvent(Event&)` method of Application and Layer
		 * Invoked immediatly after a handle is notified by the occurence of an Event
		 * Also See: Event
		 */
		using Func = std::function<void(Event&)>;

		~Window() = default;

		// Implemented per platform. Update the contents of the window.
		virtual void update() = 0;

		// Implemented per platform. Set the event callbacks that the window should receive
		virtual void setCallback(const Func& callback) = 0;

		// Implemented per platform. Returns the height of the window.
		virtual unsigned int getHeight() const = 0;

		// Implemented per platform. Returns the width of the window
		virtual unsigned int getWidth() const = 0;

		// Implemented per platform. Returns a pointer to an encapsulation of the low-level window handle.
		virtual void* getNativeWindow() const = 0;

		/**
		 * Window factory method. Implemented per platform
		 * Creates a window with the given properties
		 * @param properties WindowProperties that the returned window must have
		 * @returns unique_ptr<Windpw> Pointer to the Window implementation
		 */
		static std::unique_ptr<Window> Create(const WindowProperties& properties = WindowProperties());
	};

}