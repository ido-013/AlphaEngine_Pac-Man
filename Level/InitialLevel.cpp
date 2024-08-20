#include <iostream>
#include "InitialLevel.h"
#include "../RTTI/Registry.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/RigidBodyComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/AudioComp.h"
#include "../Serializer/Serializer.h"
#include "../Prefab/Prefab.h"

void level::InitialLevel::Init()
{
	Registry::GetInstance().FindAndCreate("TransformComp", &player);
	Registry::GetInstance().FindAndCreate("PlayerComp", &player);
	Registry::GetInstance().FindAndCreate("SpriteComp", &player);
	Registry::GetInstance().FindAndCreate("RigidbodyComp", &player);
	Registry::GetInstance().FindAndCreate("AudioComp", &player);

	player.GetComponent<TransformComp>()->SetScale({ 100, 100 });
	player.GetComponent<SpriteComp>()->SetTexture("Assets/PlanetTexture.png");
	player.GetComponent<AudioComp>()->SetAudio("Assets/bouken.mp3");

	Serializer::GetPtr()->SaveLevel("test.json");
	Prefab::SavePrefab("prefab", &player);
}

void level::InitialLevel::Update()
{

}

void level::InitialLevel::Exit()
{

}
