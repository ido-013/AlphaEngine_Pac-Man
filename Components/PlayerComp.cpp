#include "PlayerComp.h"
#include "AEEngine.h"
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "../Event/CollisionEvent.h"

PlayerComp::PlayerComp(GameObject* _owner) : LogicComponent(_owner)
{
	
}

void PlayerComp::AddScore(int _score)
{
	score += _score;
	std::cout << score << std::endl;
}

void PlayerComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	if (AEInputCheckCurr(AEVK_W) && dir != DOWN && dir != UP && !wall[UP])
	{	
		t->SetRot(PI / 2);
		t->SetPos({ targetX, targetY });
		dir = UP;
	}
	if (AEInputCheckCurr(AEVK_S) && dir != UP && dir != DOWN && !wall[DOWN])
	{
		t->SetRot(-PI / 2);
		t->SetPos({ targetX, targetY });
		dir = DOWN;
	}
	if (AEInputCheckCurr(AEVK_A) && dir != RIGHT && dir != LEFT && !wall[LEFT])
	{
		t->SetRot(PI);
		t->SetPos({ targetX, targetY });
		dir = LEFT;
	}
	if (AEInputCheckCurr(AEVK_D) && dir != LEFT && dir != RIGHT && !wall[RIGHT])
	{
		t->SetRot(0);
		t->SetPos({ targetX, targetY });
		dir = RIGHT;
	}

	if (abs(targetX - t->GetPos().x) < 1 &&
		abs(targetY - t->GetPos().y) < 1 &&
		((dir == UP && wall[UP]) ||
		(dir == DOWN && wall[DOWN]) ||
		(dir == RIGHT && wall[RIGHT]) ||
		(dir == LEFT && wall[LEFT])))
		r->ClearVelocity();

	else
		r->SetVelocity(dx[dir] * speed, dy[dir] * speed);
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
