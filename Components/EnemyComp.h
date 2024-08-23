#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"
#include "TransformComp.h"

class EnemyComp : public LogicComponent
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
	int mapPos[2];
	int spawnPos[2];
	float targetX;
	float targetY;

	TransformComp* playerTrans = nullptr;

private:
	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	float speed = 500;
	direction dir = DOWN;

public:
	EnemyComp(GameObject* _owner);
	void Update() override;
	void UpdateDir();
	void ResetPos();

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateEnemyComponent(GameObject* owner);
	static constexpr const char* TypeName = "EnemyComp";
};