#pragma once

namespace Ivy {

	class Context
	{
	public:
		virtual void init() = 0;
		virtual void refresh() = 0;

		static std::unique_ptr<Context> Create(void* window);
	};

}