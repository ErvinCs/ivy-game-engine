#pragma once

#include "Core.h"

namespace Ivy {

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getWidth() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	

	};

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
}