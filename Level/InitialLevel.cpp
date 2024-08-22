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

void level::InitialLevel::Init()
{
	Prefab p("test");
	Prefab c("coin");
	Prefab w("wall");
	Prefab e("enemy");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != '-')
			{
				GameObject* temp;

				if (map[i][j] == '1')
				{
					temp = w.NewGameObject();
					temp->SetType(Entity::Wall);
				}

				else if (map[i][j] == 'o')
				{
					temp = c.NewGameObject();
					temp->SetType(Entity::Coin);
				}

				else if (map[i][j] == 'E')
				{
					temp = e.NewGameObject();
					temp->SetType(Entity::Enemy);
				}
					
				else
				{
					temp = p.NewGameObject();
				}

				float wl = windowWidth / width;
				float hl = windowHeight / height;
				temp->GetComponent<TransformComp>()->SetScale({ wl, hl });

				float x = MapToPosX(windowWidth, wl, width, j);
				float y = MapToPosY(windowHeight, hl, height, i);
				temp->GetComponent<TransformComp>()->SetPos({ x, y });
				
				if (map[i][j] == '1')
					walls.push_back(temp);
				else if (map[i][j] == 'o')
					coins.push_back(temp);
				else if (map[i][j] == 'E')
				{

					enemies.push_back(temp);
				}
				else
				{
					playerMapPos[0] = i;
					playerMapPos[1] = j;

					auto p = temp->GetComponent<PlayerComp>();
					p->targetX = x;
					p->targetY = y;
					p->wall[p->LEFT] = (map[playerMapPos[0]][playerMapPos[1] - 1] == '1');
					p->wall[p->RIGHT] = (map[playerMapPos[0]][playerMapPos[1] + 1] == '1');
					p->wall[p->UP] = (map[playerMapPos[0] + 1][playerMapPos[1]] == '1');
					p->wall[p->DOWN] = (map[playerMapPos[0] - 1][playerMapPos[1]] == '1');

					players.push_back(temp);
				}
			}
		}
	}
}

void level::InitialLevel::Update()
{
	for (auto player : players)
	{
		auto t = player->GetComponent<TransformComp>();
		auto p = player->GetComponent<PlayerComp>();
		AEVec2 playerPos = t->GetPos();

		if (PosToMapX(windowWidth, width, playerPos.x) != playerMapPos[1]
			|| PosToMapY(windowHeight, height, playerPos.y) != playerMapPos[0])
		{
			playerMapPos[0] = PosToMapY(windowHeight, height, playerPos.y);
			playerMapPos[1] = PosToMapX(windowWidth, width, playerPos.x);

			p->targetY = MapToPosX(windowHeight, t->GetScale().y, height, playerMapPos[0]);
			p->targetX = MapToPosX(windowWidth, t->GetScale().x, width, playerMapPos[1]);
		}

		p->wall[p->LEFT] = (map[playerMapPos[0]][playerMapPos[1] - 1] == '1');
		p->wall[p->RIGHT] = (map[playerMapPos[0]][playerMapPos[1] + 1] == '1');
		p->wall[p->DOWN] = (map[playerMapPos[0] - 1][playerMapPos[1]] == '1');
		p->wall[p->UP] = (map[playerMapPos[0] + 1][playerMapPos[1]] == '1');
	}

	for (auto enemy : enemies)
	{
		auto t = enemy->GetComponent<TransformComp>();
		auto p = enemy->GetComponent<EnemyComp>();
		AEVec2 playerPos = t->GetPos();

		if (PosToMapX(windowWidth, width, playerPos.x) != playerMapPos[1]
			|| PosToMapY(windowHeight, height, playerPos.y) != playerMapPos[0])
		{
			playerMapPos[0] = PosToMapY(windowHeight, height, playerPos.y);
			playerMapPos[1] = PosToMapX(windowWidth, width, playerPos.x);

			p->targetY = MapToPosX(windowHeight, t->GetScale().y, height, playerMapPos[0]);
			p->targetX = MapToPosX(windowWidth, t->GetScale().x, width, playerMapPos[1]);
		}

		p->wall[p->LEFT] = (map[playerMapPos[0]][playerMapPos[1] - 1] == '1');
		p->wall[p->RIGHT] = (map[playerMapPos[0]][playerMapPos[1] + 1] == '1');
		p->wall[p->DOWN] = (map[playerMapPos[0] - 1][playerMapPos[1]] == '1');
		p->wall[p->UP] = (map[playerMapPos[0] + 1][playerMapPos[1]] == '1');
	}
}

void level::InitialLevel::Exit()
{
}
