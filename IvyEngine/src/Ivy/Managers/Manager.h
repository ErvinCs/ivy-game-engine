#pragma once

namespace Ivy {

	class Manager
	{
	protected:
		// Will probably become more specific
		virtual void updateHook() = 0;
		virtual void initHook() = 0;
		virtual void shutdownHook() = 0;

	public:
		// Init each subsystem in a predefined runOrder
		virtual void init() final {
			initHook();
		}

		// Shutdown each subsystem in reverse runOrder
		virtual void shutdown() final {
			shutdownHook();
		}

		// In-loop operations
		virtual void run() final {
			updateHook();
		}

		Manager() {}
		~Manager() {}
	};

}