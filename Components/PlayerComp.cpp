#include "PlayerComp.h"
#include <string>
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "SpriteComp.h"
#include "../Event/CollisionEvent.h"
#include "../Utils/Utils.h"
#include "../GSM/GameStateManager.h"
#include "../Level/GameOver.h"
#include "../Level/GameClear.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"

PlayerComp::PlayerComp(GameObject* _owner) : LogicComponent(_owner)//, pFont(AEGfxCreateFont("Assets/Arial-Italic.ttf", 20))
{
	/*Prefab lPrefab("life");
	TransformComp* t = nullptr;

	for (int i = 0; i < life; i++)
	{
		GameObject* temp = lPrefab.NewGameObject();
		t = temp->GetComponent<TransformComp>();

		float scaleX = 20;
		float scaleY = 20;
		float padding = 10;

		t->SetScale({ scaleX, scaleY });
		t->SetPos({ (i * (scaleX + 10.f)) - (windowWidth / 2) + (scaleX / 2) + padding,
					-(windowHeight / 2) + (scaleY / 2) + padding });

		lives.push_back(temp);
	}*/
}

PlayerComp::~PlayerComp()
{
	AEGfxDestroyFont(pFont);
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

	if (AEInputCheckCurr(AEVK_W) && dir != DOWN && dir != UP && !wall[UP] && !isRot)
	{	
		t->SetPos({ targetX, targetY });
		isRot = true;
		dir = UP;
	}
	if (AEInputCheckCurr(AEVK_S) && dir != UP && dir != DOWN && !wall[DOWN] && !isRot)
	{
		t->SetPos({ targetX, targetY });
		isRot = true;
		dir = DOWN;
	}
	if (AEInputCheckCurr(AEVK_A) && dir != RIGHT && dir != LEFT && !wall[LEFT] && !isRot)
	{
		t->SetPos({ targetX, targetY });
		isRot = true;
		dir = LEFT;
	}
	if (AEInputCheckCurr(AEVK_D) && dir != LEFT && dir != RIGHT && !wall[RIGHT] && !isRot)
	{
		t->SetPos({ targetX, targetY });
		isRot = true;
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

	//AEGfxPrint(pFont, std::to_string(score).c_str(), -0.99f, 0.95f, 1.f, 1.f, 1.f, 1.f, 1.f);
}

void PlayerComp::ResetPos()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	t->SetPos({ MapToPosX(spawnPos[1]), MapToPosY(spawnPos[0]) });
}

void PlayerComp::UpdateLife()
{
	life--;

	/*GameObjectManager::GetInstance().RemoveObject(lives.back());*/
	/*lives.pop_back();*/

	if (life == 0)
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new level::GameOver);
	}
	else
	{
		ResetPos();
	}
}

void PlayerComp::UpdateCoin()
{
	coinCount--;

	if (coinCount == 0)
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new level::GameClear(score));
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
