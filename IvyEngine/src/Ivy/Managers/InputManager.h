#pragma once
#include "Manager.h"


namespace Ivy {

	class InputManager : public Manager
	{
	public:
		~InputManager() = default;

		static InputManager& getInstance()
		{
			static InputManager instance{};
			return instance;
		}

	protected:
		void initHook();
		void updateHook();
		void shutdownHook();

		InputManager() {}
		InputManager(const InputManager&) = delete;
		InputManager& operator=(const InputManager&) = delete;
	};

}
