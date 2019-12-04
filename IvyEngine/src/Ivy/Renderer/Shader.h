#pragma once

namespace Ivy {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static std::shared_ptr<Shader> Create(const std::string& filepath);
	};

}