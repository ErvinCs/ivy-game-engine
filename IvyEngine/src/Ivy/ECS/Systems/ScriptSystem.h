#pragma once

#include "System.h"

namespace Ivy {
	/**
	 * System used to control entity behavior by calling external AS scripts.
	 * Requires a ScriptComponent
	 * @see System
	 * @see ScriptComponent
	 */
	class ScriptSystem : public System
	{
	public:
		ScriptSystem() = default;
		ScriptSystem(EntityContainer& entities)
		{
			this->setEntities(entities);		
		}

		/**
		 * Creates script controllers for all scripts available at initialization time
		 */
		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}
