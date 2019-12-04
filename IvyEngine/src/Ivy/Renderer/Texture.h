#pragma once

namespace Ivy {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void bind(unsigned int slot = 0) const = 0;
		virtual void unbind() const = 0 ;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void flipX() const = 0;
		virtual void flipY() const = 0;

		static std::shared_ptr<Texture> Create(const std::string& filepath);
	};

}