#pragma once

#include <string>
#include "../Component.h"
#include "../../Renderer/Texture.h"

namespace Ivy
{
	/*
	 *
	 */
	struct Renderable : public Component
	{
	public:
		std::string spritePath;
		std::shared_ptr<Ivy::Texture> texture;

		Renderable() : Component() 
		{
			spritePath = "blank.png";
		}
		Renderable(std::string spritePath);
		Renderable(const Renderable& other);

		inline void addReference() { /* do nothing */ }
		inline void release() { /* do nothing */ }

		Renderable& operator=(const Renderable& other);
	};
}