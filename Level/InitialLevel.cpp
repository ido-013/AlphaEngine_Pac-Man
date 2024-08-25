#include <iostream>
#include "InitialLevel.h"
#include "../RTTI/Registry.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/RigidBodyComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/AudioComp.h"
#include "../Components/EnemyComp.h"
#include "../Serializer/Serializer.h"
#include "../Prefab/Prefab.h"
#include "../Utils/Utils.h"
#include "../Map/Map.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../EventManager/EventManager.h"

void level::InitialLevel::Init()
{
	Prefab pPrefab("test");
	Prefab cPrefab("coin");
	Prefab wPrefab("wall");
	Prefab ePrefab("enemy");

	TransformComp* t = nullptr;
	SpriteComp* s = nullptr;
	PlayerComp* p = nullptr;
	EnemyComp* e = nullptr;
	GameObject* temp = nullptr;

	int enemyInd = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != '-')
			{
				if (map[i][j] == '1')
				{
					temp = wPrefab.NewGameObject();
					temp->SetType(Entity::Wall);
				}

				else if (map[i][j] == 'o')
				{
					temp = cPrefab.NewGameObject();
					temp->SetType(Entity::Coin);
					coinCount++;
				}

				else if (map[i][j] == 'E')
				{
					temp = ePrefab.NewGameObject();
					temp->SetType(Entity::Enemy);
				}

				else if (map[i][j] == 'P')
				{
					temp = wPrefab.NewGameObject();
					temp->SetType(Entity::Wall);
				}

				else if (map[i][j] == '*')
				{
					temp = cPrefab.NewGameObject();
					temp->SetType(Entity::Super);
				}

				else
				{
					temp = pPrefab.NewGameObject();
					temp->SetType(Entity::Player);
				}

				t = temp->GetComponent<TransformComp>();

				t->SetScale({ windowWidth / width, windowHeight / height });

				float x = MapToPosX(j);
				float y = MapToPosY(i);
				t->SetPos({ x, y });
				
				if (map[i][j] == '1')
				{
					
				}

				else if (map[i][j] == 'o')
				{
					t->SetScale({ t->GetScale().x / 2.f, t->GetScale().y / 2.f });
				}

				else if (map[i][j] == 'E')
				{
					e = temp->GetComponent<EnemyComp>();

					e->mapPos[0] = i;
					e->mapPos[1] = j;
					e->spawnPos[0] = i;
					e->spawnPos[1] = j;
					e->targetX = x;
					e->targetY = y;
					e->wall[e->LEFT]  =	(map[e->mapPos[0]][e->mapPos[1] - 1] == '1');
					e->wall[e->RIGHT] = (map[e->mapPos[0]][e->mapPos[1] + 1] == '1');
					e->wall[e->UP]    =	(map[e->mapPos[0] + 1][e->mapPos[1]] == '1');
					e->wall[e->DOWN]  =	(map[e->mapPos[0] - 1][e->mapPos[1]] == '1');
					enemies[enemyInd] = temp;
					enemyInd++;
				}

				else if (map[i][j] == 'P')
				{
					s = temp->GetComponent<SpriteComp>();
					s->SetColor(0, 255, 0);
				}

				else if (map[i][j] == '*')
				{
					s = temp->GetComponent<SpriteComp>();
					t->SetScale({ t->GetScale().x / 1.2f, t->GetScale().y / 1.2f });
					s->SetColor(0, 0, 255);
				}

				else
				{
					p = temp->GetComponent<PlayerComp>();

					p->mapPos[0] = i;
					p->mapPos[1] = j;
					p->spawnPos[0] = i;
					p->spawnPos[1] = j;
					p->targetX = x;
					p->targetY = y;
					p->wall[p->LEFT]  =	(map[p->mapPos[0]][p->mapPos[1] - 1] == '1') || (map[p->mapPos[0]][p->mapPos[1] - 1] == 'P');
					p->wall[p->RIGHT] = (map[p->mapPos[0]][p->mapPos[1] + 1] == '1') || (map[p->mapPos[0]][p->mapPos[1] + 1] == 'P');
					p->wall[p->UP]    =	(map[p->mapPos[0] + 1][p->mapPos[1]] == '1') || (map[p->mapPos[0] + 1][p->mapPos[1]] == 'P');
					p->wall[p->DOWN]  =	(map[p->mapPos[0] - 1][p->mapPos[1]] == '1') || (map[p->mapPos[0] - 1][p->mapPos[1]] == 'P');

					player = temp;
				}
			}
		}
	}

	for (auto enemy : enemies)
	{
		e = enemy->GetComponent<EnemyComp>();
		e->playerTrans = player->GetComponent<TransformComp>();
	}

	p->coinCount = coinCount;
}

void level::InitialLevel::Update()
{
	TransformComp* t = nullptr;
	SpriteComp* s = nullptr;
	EnemyComp* e = nullptr;
	PlayerComp* p = nullptr;

	p = player->GetComponent<PlayerComp>();

	for (auto enemy : enemies)
	{
		t = enemy->GetComponent<TransformComp>();
		s = enemy->GetComponent<SpriteComp>();
		e = enemy->GetComponent<EnemyComp>();
		AEVec2 enemyPos = t->GetPos();

		if (PosToMapX(enemyPos.x) != e->mapPos[1]
			|| PosToMapY(enemyPos.y) != e->mapPos[0])
		{
			e->mapPos[0] = PosToMapY(enemyPos.y);
			e->mapPos[1] = PosToMapX(enemyPos.x);

			e->targetY = MapToPosY(e->mapPos[0]);
			e->targetX = MapToPosX(e->mapPos[1]);

			if (e->isRot)
				e->isRot = false;

			e->wall[e->LEFT]	= (map[e->mapPos[0]][e->mapPos[1] - 1] == '1') || ((map[e->mapPos[0]][e->mapPos[1] - 1] == 'P') && e->isOut);
			e->wall[e->RIGHT]	= (map[e->mapPos[0]][e->mapPos[1] + 1] == '1') || ((map[e->mapPos[0]][e->mapPos[1] + 1] == 'P') && e->isOut);
			e->wall[e->UP]		= (map[e->mapPos[0] + 1][e->mapPos[1]] == '1') || ((map[e->mapPos[0] + 1][e->mapPos[1]] == 'P') && e->isOut);
			e->wall[e->DOWN]	= (map[e->mapPos[0] - 1][e->mapPos[1]] == '1') || ((map[e->mapPos[0] - 1][e->mapPos[1]] == 'P') && e->isOut);

			e->UpdateDir();
		}

		if (p->superMode)
		{
			s->SetColor(0, 0, 255);
			e->speed = 60;
		}
		else
		{
			s->SetColor(255, 0, 0);
			e->speed = 100;
		}
	}

	t = player->GetComponent<TransformComp>();
	AEVec2 playerPos = t->GetPos();

	if (PosToMapX(playerPos.x) != p->mapPos[1]
		|| PosToMapY(playerPos.y) != p->mapPos[0])
	{
		p->mapPos[0] = PosToMapY(playerPos.y);
		p->mapPos[1] = PosToMapX(playerPos.x);

		p->targetY = MapToPosX(p->mapPos[0]);
		p->targetX = MapToPosX(p->mapPos[1]);

		if (p->isRot)
			p->isRot = false;
	}

	p->wall[p->LEFT]  =	(map[p->mapPos[0]][p->mapPos[1] - 1] == '1') || (map[p->mapPos[0]][p->mapPos[1] - 1] == 'P');
	p->wall[p->RIGHT] = (map[p->mapPos[0]][p->mapPos[1] + 1] == '1') || (map[p->mapPos[0]][p->mapPos[1] + 1] == 'P');
	p->wall[p->UP]    =	(map[p->mapPos[0] + 1][p->mapPos[1]] == '1') || (map[p->mapPos[0] + 1][p->mapPos[1]] == 'P');
	p->wall[p->DOWN]  =	(map[p->mapPos[0] - 1][p->mapPos[1]] == '1') || (map[p->mapPos[0] - 1][p->mapPos[1]] == 'P');
}

void level::InitialLevel::Exit()
{
	GameObjectManager::GetInstance().RemoveAllObject();
	EventManager::GetInstance().DeleteUndispahchEvent();
}
