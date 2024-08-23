#include "PlayerComp.h"
#include "AEEngine.h"
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "SpriteComp.h"
#include "../Event/CollisionEvent.h"
#include "../Utils/Utils.h"
#include "../GSM/GameStateManger.h"
#include "../Level/GameOver.h"

PlayerComp::PlayerComp(GameObject* _owner) : LogicComponent(_owner)
{
	
}

void PlayerComp::AddScore(int _score)
{
	score += _score;
}

void PlayerComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	SpriteComp* s = owner->GetComponent<SpriteComp>();
	if (!s) return;

	if (superMode)
	{
		static float time = 0;
		time += AEFrameRateControllerGetFrameTime();

		s->SetColor(0, 0, 255);
		speed = 200;

		if (time > 5)
		{
			superMode = false;
			s->SetColor(255, 255, 255);
			speed = 100;
			time = 0;
		}
	}

	if (AEInputCheckCurr(AEVK_W) && dir != DOWN && dir != UP && !wall[UP])
	{	
		t->SetPos({ targetX, targetY });
		dir = UP;
	}
	if (AEInputCheckCurr(AEVK_S) && dir != UP && dir != DOWN && !wall[DOWN])
	{
		t->SetPos({ targetX, targetY });
		dir = DOWN;
	}
	if (AEInputCheckCurr(AEVK_A) && dir != RIGHT && dir != LEFT && !wall[LEFT])
	{
		t->SetPos({ targetX, targetY });
		dir = LEFT;
	}
	if (AEInputCheckCurr(AEVK_D) && dir != LEFT && dir != RIGHT && !wall[RIGHT])
	{
		t->SetPos({ targetX, targetY });
		dir = RIGHT;
	}

	t->SetRot((PI / 2) * dir);

	if (abs(targetX - t->GetPos().x) < 10 &&
		abs(targetY - t->GetPos().y) < 10 &&
		((dir == UP && wall[UP]) ||
		(dir == DOWN && wall[DOWN]) ||
		(dir == RIGHT && wall[RIGHT]) ||
		(dir == LEFT && wall[LEFT])))
		r->ClearVelocity();

	else
		r->SetVelocity(dx[dir] * speed, dy[dir] * speed);
}

void PlayerComp::ResetPos()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	t->SetPos({ MapToPosX(spawnPos[1]), MapToPosY(spawnPos[0]) });
}

void PlayerComp::AddLife(int value)
{
	life += value;

	if (life == 0)
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new level::GameOver);
	}
	else
	{
		ResetPos();
	}
}

void PlayerComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();
	}
}

json PlayerComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	data["compData"] = compData;

	return data;
}

BaseRTTI* PlayerComp::CreatePlayerComponent(GameObject* owner)
{
	BaseRTTI* p = new PlayerComp(owner);
	owner->AddComponent<PlayerComp>(static_cast<BaseComponent*>(p));
	return p;
}
