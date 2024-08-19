#include "TransformTest.h"
#include "../GSM/GameStateManger.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/RigidbodyComp.h"
#include "../Components/ColliderComp.h"
#include "../EventManager/EventManager.h"
#include <iostream>

GameObject* player = nullptr;
GameObject* coin = nullptr;
GameObject* flag = nullptr;

void Levels::TransformTest::Init()
{
	player = new GameObject();
	coin = new GameObject();
	flag = new GameObject();

	//
	coin->AddComponent<TransformComp>();
	coin->AddComponent<SpriteComp>();
	coin->AddComponent<ColliderComp>();

	TransformComp* ct = coin->GetComponent<TransformComp>();
	ct->SetScale({ 100, 100 });
	ct->SetPos({ 300, 0 });

	SpriteComp* cs = coin->GetComponent<SpriteComp>();
	cs->SetTexture("Assets/coin.png");

	ColliderComp* cc = coin->GetComponent<ColliderComp>();
	cc->SetType(Entity::Coin);

	//
	flag->AddComponent<TransformComp>();
	flag->AddComponent<SpriteComp>();
	flag->AddComponent<ColliderComp>();

	TransformComp* ft = flag->GetComponent<TransformComp>();
	ft->SetScale({ 100, 100 });
	ft->SetPos({ -300, 0 });

	SpriteComp* fs = flag->GetComponent<SpriteComp>();
	fs->SetTexture("Assets/coin.png");

	ColliderComp* fc = flag->GetComponent<ColliderComp>();
	fc->SetType(Entity::Flag);

	//
	player->AddComponent<TransformComp>();
	player->AddComponent<SpriteComp>();
	player->AddComponent<RigidbodyComp>();
	player->AddComponent<PlayerComp>();
	player->AddComponent<AudioComp>();

	PlayerComp* pp = player->GetComponent<PlayerComp>();

	TransformComp* pt = player->GetComponent<TransformComp>();
	pt->SetScale({ 100, 100 });

	SpriteComp* ps = player->GetComponent<SpriteComp>();
	ps->SetTexture("Assets/PlanetTexture.png");

	AudioComp* pa = player->GetComponent<AudioComp>();
	pa->SetAudio("Assets/Audio/bouken.mp3");

	//
	EventManager::GetEMPtr()->RegisterEntity<CollisionEvent>(pp);
	fc->AddTrans(pt);
	cc->AddTrans(pt);
}

void Levels::TransformTest::Update()
{
	//trs->PrintMatrix();
}

void Levels::TransformTest::Exit()
{}
