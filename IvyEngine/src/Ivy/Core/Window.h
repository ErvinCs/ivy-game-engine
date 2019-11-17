#pragma once

#include <string>
#include "../Events/Event.h"
namespace Ivy {

	struct WindowProperties
	{
		std::string name;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& name = "Ivy",
			unsigned int width = 1280,
			unsigned int height = 720)
			: name(name), width(width), height(height)
		{}
	};

	class Window
	{
	public:
		using Func = std::function<void(Event&)>;

		~Window() = default;

		virtual void update() = 0;
		virtual void setCallback(const Func& callback) = 0;

		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getWidth() const = 0;

		// Window factory method - implemented per platform
		static Window* Create(const WindowProperties& properties = WindowProperties());
	};

}