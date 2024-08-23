#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"

class PlayerComp : public LogicComponent
{
public:
	enum direction
	{
		RIGHT = 0,
		UP = 1,
		LEFT = 2,
		DOWN = 3,
	};

	bool wall[4] = { false };
	bool superMode = false;
	int mapPos[2];
	int spawnPos[2];
	float targetX;
	float targetY;

private:
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	float speed = 500;
	int life = 1;
	direction dir = RIGHT;

	int score = 0;

public:
	PlayerComp(GameObject* _owner);
	void AddScore(int _score); 
	void Update() override;
	void ResetPos();
	void AddLife(int);

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";
};