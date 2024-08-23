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

void level::InitialLevel::Init()
{
	Prefab pPrefab("test");
	Prefab cPrefab("coin");
	Prefab wPrefab("wall");
	Prefab ePrefab("enemy");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != '-')
			{
				GameObject* temp;

				if (map[i][j] == '1')
				{
					temp = wPrefab.NewGameObject();
					temp->SetType(Entity::Wall);
				}

				else if (map[i][j] == 'o')
				{
					temp = cPrefab.NewGameObject();
					temp->SetType(Entity::Coin);
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
				}

				temp->GetComponent<TransformComp>()->SetScale({ windowWidth / width, windowHeight / height });

				float x = MapToPosX(j);
				float y = MapToPosY(i);
				temp->GetComponent<TransformComp>()->SetPos({ x, y });
				
				if (map[i][j] == '1')
				{
					walls.push_back(temp);
				}

				else if (map[i][j] == 'o')
				{
					auto t = temp->GetComponent<TransformComp>();
					t->SetScale({ t->GetScale().x / 2.f, t->GetScale().y / 2.f });
					coins.push_back(temp);
				}

				else if (map[i][j] == 'E')
				{
					auto e = temp->GetComponent<EnemyComp>();
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
					enemies.push_back(temp);
				}

				else if (map[i][j] == 'P')
				{
					auto s = temp->GetComponent<SpriteComp>();
					s->SetColor(0, 255, 0);
				}

				else if (map[i][j] == '*')
				{
					auto s = temp->GetComponent<SpriteComp>();
					s->SetColor(0, 0, 255);
				}

				else
				{
					auto p = temp->GetComponent<PlayerComp>();
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
					players.push_back(temp);
				}
			}
		}
	}

	for (auto enemy : enemies)
	{
		auto e = enemy->GetComponent<EnemyComp>();
		e->playerTrans = players[0]->GetComponent<TransformComp>();
	}
}

void level::InitialLevel::Update()
{
	for (auto enemy : enemies)
	{
		auto t = enemy->GetComponent<TransformComp>();
		auto e = enemy->GetComponent<EnemyComp>();
		AEVec2 enemyPos = t->GetPos();

		if (PosToMapX(enemyPos.x) != e->mapPos[1]
			|| PosToMapY(enemyPos.y) != e->mapPos[0])
		{
			e->mapPos[0] = PosToMapY(enemyPos.y);
			e->mapPos[1] = PosToMapX(enemyPos.x);

			e->targetY = MapToPosX(e->mapPos[0]);
			e->targetX = MapToPosX(e->mapPos[1]);
		}

		e->wall[e->LEFT]  =	(map[e->mapPos[0]][e->mapPos[1] - 1] == '1');
		e->wall[e->RIGHT] = (map[e->mapPos[0]][e->mapPos[1] + 1] == '1');
		e->wall[e->DOWN]  =	(map[e->mapPos[0] - 1][e->mapPos[1]] == '1');
		e->wall[e->UP]    =	(map[e->mapPos[0] + 1][e->mapPos[1]] == '1');
	}

	for (auto player : players)
	{
		auto t = player->GetComponent<TransformComp>();
		auto p = player->GetComponent<PlayerComp>();
		AEVec2 playerPos = t->GetPos();

		if (PosToMapX(playerPos.x) != p->mapPos[1]
			|| PosToMapY(playerPos.y) != p->mapPos[0])
		{
			p->mapPos[0] = PosToMapY(playerPos.y);
			p->mapPos[1] = PosToMapX(playerPos.x);

			p->targetY = MapToPosX(p->mapPos[0]);
			p->targetX = MapToPosX(p->mapPos[1]);
		}

		p->wall[p->LEFT]  =	(map[p->mapPos[0]][p->mapPos[1] - 1] == '1') || (map[p->mapPos[0]][p->mapPos[1] - 1] == 'P');
		p->wall[p->RIGHT] = (map[p->mapPos[0]][p->mapPos[1] + 1] == '1') || (map[p->mapPos[0]][p->mapPos[1] + 1] == 'P');
		p->wall[p->UP]    =	(map[p->mapPos[0] + 1][p->mapPos[1]] == '1') || (map[p->mapPos[0] + 1][p->mapPos[1]] == 'P');
		p->wall[p->DOWN]  =	(map[p->mapPos[0] - 1][p->mapPos[1]] == '1') || (map[p->mapPos[0] - 1][p->mapPos[1]] == 'P');
	}
}

void level::InitialLevel::Exit()
{
	GameObjectManager::GetInstance().RemoveAllObject();
}
