#pragma once

#include <Ivy.h>

static ComponentType UserCompID = Ivy::ECS::getInstance().generateComponentId();

class UserComponent : public Ivy::Component
{
public:
	float aField;
	std::string anotherField;

	UserComponent() : Component() {}
	UserComponent(float aField, std::string anotherField)
	{
		this->aField = aField;
		this->setComponentId(UserCompID);
		this->anotherField = anotherField;
	}
};

void loadUC(Entity& entity, nlohmann::json& json)
{
	if (!json["components"]["user_component"].is_null())
	{
		float aField;
		std::string anotherField;
		json["components"]["user_component"]["a_field"].get_to(aField);
		json["components"]["user_component"]["other_field"].get_to(anotherField);
		UserComponent userComp{ aField, anotherField };
		Ivy::ECS::getInstance().addComponent<UserComponent>(entity, userComp);

	}
}

void saveUC(Entity& entity, nlohmann::json& json)
{
	nlohmann::json jsonNull;
	if (Ivy::ECS::getInstance().getComponent<UserComponent>(entity).getEntityId() != entity)
	{
		json["components"]["user_component"] = jsonNull;
	}
	else {
		UserComponent userComp = Ivy::ECS::getInstance().getComponent<UserComponent>(entity);
		json["components"]["user_component"]["a_field"] = userComp.aField;
		json["components"]["user_component"]["other_field"] = userComp.anotherField;
	}
}


class UserComponentSystem : public Ivy::System
{
public:
	UserComponentSystem() = default;
	UserComponentSystem(EntityContainer& entities)
	{
		this->setEntities(entities);
	}

	virtual void init() override
	{
		Ivy::ECS::getInstance().addComponentType<UserComponent>();
		IVY_TRACE("Initializing UserComponentSystem");
	}

	virtual void update(float deltatime) override
	{
		for (auto& it = entities->begin(); it != entities->end(); it++)
		{
			auto& object = *it;

			auto& userComp = Ivy::ECS::getInstance().getComponent<UserComponent>(object);
			if (userComp.getComponentId() != UserCompID)
				continue;

			userComp.aField += 0.1f;
			if (userComp.aField == 100000.0f)
				userComp.aField = 0;
		}
	}
};