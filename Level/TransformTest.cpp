#include "TransformTest.h"
#include "../GSM/GameStateManger.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/RigidbodyComp.h"
#include "../Components/EnemyComp.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include <iostream>

GameObject* player = nullptr;
GameObject* coin = nullptr;
GameObject* flag = nullptr;

void level::TransformTest::Init()
{
	coin = new GameObject();

	coin->AddComponent<TransformComp>();
	coin->AddComponent<SpriteComp>();
	coin->AddComponent<RigidbodyComp>();
	coin->AddComponent<EnemyComp>();

	coin->SetType(Entity::Enemy);

	TransformComp* ct = coin->GetComponent<TransformComp>();
	ct->SetScale({ 100, 100 });
	ct->SetPos({ 0, 0 });

	SpriteComp* cs = coin->GetComponent<SpriteComp>();
	cs->SetTexture("Assets/arrow.png");
	cs->SetColor(255, 0, 0);

	Prefab::SavePrefab("enemy", coin);
}

void level::TransformTest::Update()
{

}

void level::TransformTest::Exit()
{}
