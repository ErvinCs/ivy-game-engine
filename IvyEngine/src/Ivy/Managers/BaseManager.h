#pragma once

namespace Ivy {

	class BaseManager
	{
	protected:
		// Will probably become more specific
		virtual void updateHook() = 0;
		virtual void initHook() = 0;
		virtual void shutdownHook() = 0;

	public:
		// Init each subsystem in a predefined runOrder
		virtual void init() final {
			// Init common operations & hooks
		}

		// Shutdown each subsystem in reverse runOrder
		virtual void shutdown() final {
			// Shutdown common operations & hooks
		}

		// In-loop operations
		virtual void run() final {
			updateHook();
		}

		BaseManager() {}
		~BaseManager() {}
	};

}