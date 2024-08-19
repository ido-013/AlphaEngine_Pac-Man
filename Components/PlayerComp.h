#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"

class PlayerComp : public LogicComponent
{
private:
	float speed = 10;
	long score = 0;

public:
	PlayerComp(GameObject* _owner);
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";
};