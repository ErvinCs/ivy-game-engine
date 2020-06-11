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
	UserComponentSystem(Ivy::EntityContainer& entities)
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

/* Construct Code
		Ivy::JSONManager::addLoadFunction(loadUC);
		Ivy::JSONManager::addSaveFunction(saveUC);
*/
/* imGuiRender Code
		static std::string tagTemp;
		ImGui::Begin("User Components");
		for (Entity& entity : Ivy::ECS::getInstance().getEntities())
		{
			ImGui::PushID(&entity);
			if (Ivy::ECS::getInstance().getComponent<Ivy::Tag>(entity).getComponentId() ==
				Ivy::ECS::getInstance().getComponentTypes().find(typeid(Ivy::Tag).name())->second
				&& tagTemp.size() > 0)
			{
				tagTemp = Ivy::ECS::getInstance().getComponent<Ivy::Tag>(entity).tag;
			}
			else
			{
				tagTemp = "Entity##";
			}

			if (ImGui::CollapsingHeader(tagTemp.c_str()))
			{
				if (ImGui::TreeNode("UserComp"))
				{
					if (Ivy::ECS::getInstance().getComponent<UserComponent>(entity).getComponentId() == UserCompID)
					{
						ImGui::InputFloat("aField", (float*)&Ivy::ECS::getInstance().getComponent<UserComponent>(entity).aField, 2);
						if (ImGui::Button("Remove UserComp"))
						{
							Ivy::ECS::getInstance().removeComponent<UserComponent>(entity);
							IVY_INFO("Destroyed UserComponent on Entity: {0}", entity);
						}
					}
					else
					{
						if (ImGui::Button("Add UserComp"))
						{
							UserComponent newUserComp = UserComponent(0.001f, "Hello World");
							newUserComp.setComponentId(UserCompID);
							Ivy::ECS::getInstance().addComponent<UserComponent>(entity, newUserComp);
							IVY_INFO("Added: User Component");
						}
					}
					ImGui::TreePop();
				}
			}
			ImGui::PopID();
		}
		ImGui::End();
*/