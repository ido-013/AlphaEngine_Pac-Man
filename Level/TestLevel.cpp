#include "TestLevel.h"
#include "../Serializer/Serializer.h"

void level::TestLevel::Init()
{
	Serializer::GetInstance().LoadLevel("test.json");
}

void level::TestLevel::Update()
{

}

void level::TestLevel::Exit()
{

}
