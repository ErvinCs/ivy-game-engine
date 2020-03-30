#pragma once

#include "System.h"

namespace Ivy {

	class ScriptSystem : public System
	{
	private:

	public:
		ScriptSystem() = default;
		ScriptSystem(std::vector<Entity>& entities)
		{
			this->setEntities(entities);		
		}

		virtual void init() override;
		virtual void update(float deltatime) override;
	};

}
