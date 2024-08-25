#pragma once
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"
#include "TransformComp.h"
#include "../Level/InitialLevel.h"

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

private:
	bool wall[4] = { false };
	bool isRot = true;
	bool isOut = false;

	float ghostTimer = 0;
	float noneTimer = 0;

	int mapPos[2];
	int spawnPos[2];

	float targetX;
	float targetY;

	float dstX;
	float dstY;

	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	direction dir = DOWN;

	float speed = 500;
	
	TransformComp* playerTrans = nullptr;

public:
	EnemyComp(GameObject* _owner);
	void Update() override;
	void UpdateDir();

	void ResetPos();
	void InitGhost();

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateEnemyComponent(GameObject* owner);
	static constexpr const char* TypeName = "EnemyComp";

	friend level::InitialLevel;
	friend GameObject;
};