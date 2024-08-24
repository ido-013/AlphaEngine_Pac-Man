#include "TransformTest.h"
#include "../GSM/GameStateManager.h"
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

GameObject* temp = nullptr;

void level::TransformTest::Init()
{
	temp = new GameObject();

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();

	TransformComp* ct = temp->GetComponent<TransformComp>();
	ct->SetScale({ 100, 100 });
	ct->SetPos({ 0, 0 });

	SpriteComp* cs = temp->GetComponent<SpriteComp>();
	cs->SetTexture("Assets/heart.png");
	cs->SetColor(0, 0, 0);

	Prefab::SavePrefab("life", temp);
}

void level::TransformTest::Update()
{

}

void level::TransformTest::Exit()
{}
