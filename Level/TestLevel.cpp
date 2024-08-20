#include "TestLevel.h"
#include "../Serializer/Serializer.h"
#include "../Prefab/Prefab.h"
#include "../Components/TransformComp.h"
#include "../Components/PlayerComp.h"

GameObject* a = nullptr;
GameObject* b = nullptr;

void level::TestLevel::Init()
{
	//Serializer::GetInstance().LoadLevel("test.json");
	Prefab p("test");
	a = p.NewGameObject();
	b = p.NewGameObject();

	b->GetComponent<TransformComp>()->SetPos({ 100, 100 });
	b->DeleteComponent<PlayerComp>();
}

void level::TestLevel::Update()
{

}

void level::TestLevel::Exit()
{
	delete a;
	delete b;
}
