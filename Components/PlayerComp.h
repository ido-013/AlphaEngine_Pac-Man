#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"

class PlayerComp : public LogicComponent
{
public:
	enum direction
	{
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3,
	};

	bool wall[4] = { false };
	float targetX;
	float targetY;

private:
	int dx[4] = { 0, 1, 0, -1 };
	int dy[4] = { 1, 0, -1, 0 };
	float speed = 500;
	int score = 0;
	direction dir = RIGHT;

public:
	PlayerComp(GameObject* _owner);
	void AddScore(int _score); 
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";
};