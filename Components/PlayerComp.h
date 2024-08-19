#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"

class PlayerComp : public LogicComponent, public Entity
{
private:
	float speed = 100;
	long score = 0;

public:
	PlayerComp(GameObject* _owner);
	void OnEvent(Event* event) override;
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";
};