#pragma once
#include "AEEngine.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"
#include "../Level/InitialLevel.h"

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

private:
	bool wall[4] = { false };
	bool superMode = false;
	bool isRot = false;

	int mapPos[2];
	int spawnPos[2];

	float targetX;
	float targetY;

	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };
	direction dir = RIGHT;

	float speed = 500;

	int life = 3;
	int score = 0;
	int coinCount = 0;
	
	std::vector<GameObject*> lives;
	s8 pFont;

public:
	PlayerComp(GameObject* _owner);
	~PlayerComp();
	void AddScore(int _score); 
	void Update() override;
	void ResetPos();
	void UpdateLife();
	void UpdateCoin();

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";

	friend level::InitialLevel;
	friend GameObject;
};