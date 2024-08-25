#include "EnemyComp.h"
#include "AEEngine.h"
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "SpriteComp.h"
#include "../Event/CollisionEvent.h"
#include "../Utils/Utils.h"

EnemyComp::EnemyComp(GameObject* _owner) : LogicComponent(_owner)
{

}

void EnemyComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return; 

	SpriteComp* s = owner->GetComponent<SpriteComp>();
	if (!s) return;

	if (owner->GetType() == Entity::Enemy)
	{
		s->SetColor(255, 0, 0);
		speed = 100;
		ghostTimer = 0;
		noneTimer = 0;
	}
	else if (owner->GetType() == Entity::Ghost)
	{
		s->SetColor(0, 0, 255);
		speed = 60;

		ghostTimer += AEFrameRateControllerGetFrameTime();
		if (ghostTimer > 10)
		{
			ghostTimer = 0;
			owner->SetType(Entity::Enemy);
		}
	}
	else
	{
		s->SetColor(255, 255, 0);
		speed = 200;

		noneTimer += AEFrameRateControllerGetFrameTime();
		if (noneTimer > 3)
		{
			noneTimer = 0;
			owner->SetType(Entity::Enemy);
		}
	}

	if (abs(targetX - t->GetPos().x) < 3 &&
		abs(targetY - t->GetPos().y) < 3 &&
		!isRot &&
		((dir == UP && wall[UP]) ||
			(dir == DOWN && wall[DOWN]) ||
			(dir == RIGHT && wall[RIGHT]) ||
			(dir == LEFT && wall[LEFT])))
	{
		for (int i = 0, r = rand() % 4; i < 4; i++)
		{
			if (r == (dir + 2) % 4 || wall[r] || dir == r)
			{
				r++;
				r %= 4;
			}
			else
			{
				dir = direction(r);
				t->SetPos({ targetX, targetY });
				break;
			}
		}

		if (!isOut)
			isOut = true;

		isRot = true;
	}
	
	r->SetVelocity(dx[dir] * speed, dy[dir] * speed);
	t->SetRot((PI / 2) * dir);
}

void EnemyComp::UpdateDir()
{
	TransformComp* t = owner->GetComponent<TransformComp>();

	int emptyCount = 0;

	for (int i = 0; i < 4; i++)
	{
		if (i == (dir + 2) % 4)
			continue;

		if (!wall[i])
			emptyCount++;
	}

	if (emptyCount > 1 && isOut)
	{
		float min = 10'000'000;
		direction tempDir;

		for (int i = 0; i < 4; i++)
		{
			if (i == (dir + 2) % 4 || wall[i])
				continue;

			float y = MapToPosY(mapPos[0] + dy[i]);
			float x = MapToPosX(mapPos[1] + dx[i]);

			if (owner->GetType() == Entity::Specter)
			{
				dstY = MapToPosY(spawnPos[0]);
				dstX = MapToPosX(spawnPos[1]);
			}
			else
			{
				dstX = playerTrans->GetPos().x;
				dstY = playerTrans->GetPos().y;
			}

			float dis = GetSqDistance(dstX, dstY, x, y);

			if (dis < min)
			{
				min = dis;
				tempDir = direction(i);
			}
		}

		if (dir != tempDir)
		{
			t->SetPos({ targetX, targetY });
			dir = tempDir;
		}
	}
}

void EnemyComp::ResetPos()
{
	auto t = owner->GetComponent<TransformComp>();
	t->SetPos({ MapToPosX(spawnPos[1]), MapToPosY(spawnPos[0]) });
	dir = DOWN;
	isOut = false;
	isRot = true;
}

void EnemyComp::InitGhost()
{
	owner->SetType(Entity::Ghost);
	ghostTimer = 0;
}

void EnemyComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();
	}
}

json EnemyComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	data["compData"] = compData;

	return data;
}

BaseRTTI* EnemyComp::CreateEnemyComponent(GameObject* owner)
{
	BaseRTTI* p = new EnemyComp(owner);
	owner->AddComponent<EnemyComp>(static_cast<BaseComponent*>(p));
	return p;
}
