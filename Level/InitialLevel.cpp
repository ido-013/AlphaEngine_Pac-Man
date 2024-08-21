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
	Prefab p("test");
	GameObject* player = p.NewGameObject();
	Serializer::GetInstance().SaveLevel("test.json");
}

void level::InitialLevel::Update()
{

}

void level::InitialLevel::Exit()
{
}
