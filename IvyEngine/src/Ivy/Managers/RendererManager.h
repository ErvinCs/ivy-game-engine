#pragma once
#include "Manager.h"

namespace Ivy {

	class RendererManager : public Manager
	{
	public:
		~RendererManager() = default;

		static RendererManager& getInstance()
		{
			static RendererManager instance{};
			return instance;
		}

	protected:
		void initHook();
		void updateHook();
		void shutdownHook();

		RendererManager() {}
		RendererManager(const RendererManager&) = delete;
		RendererManager& operator=(const RendererManager&) = delete;
	};

}