#pragma once

#include <string>

namespace Ivy {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void bind(uint32_t slot = 0) const = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void flipX() = 0;
		virtual void flipY() = 0;

		static std::shared_ptr<Texture> Create(const std::string& filepath, bool isBaseTexture = false);
	};

}