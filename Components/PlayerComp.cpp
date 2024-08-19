#include "AEEngine.h"
#include "PlayerComp.h"
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "../Event/CollisionEvent.h"
#include "../GSM/GameStateManger.h"

PlayerComp::PlayerComp(GameObject* _owner) : LogicComponent(_owner)
{
	
}

void PlayerComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	//Check for input
	bool flag = false;

	if (AEInputCheckCurr(AEVK_W))
	{
		r->AddAcceleration(0, speed);
		flag = true;
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		r->AddAcceleration(0, -speed);
		flag = true;
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		r->AddAcceleration(-speed, 0);
		flag = true;
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		r->AddAcceleration(speed, 0);
		flag = true;
	}

	if (AEInputCheckCurr(AEVK_SPACE) || !flag)
	{
		r->ClearAcceleration();
	}

	if (AEInputCheckCurr(AEVK_Q))
	{
		t->SetRot(t->GetRot() - 0.5f);
	}
	if (AEInputCheckCurr(AEVK_E))
	{
		t->SetRot(t->GetRot() + 0.5f);
	}
}

void PlayerComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();
	}
}

json PlayerComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	data["compData"] = compData;

	return data;
}

BaseRTTI* PlayerComp::CreatePlayerComponent(GameObject* owner)
{
	BaseRTTI* p = new PlayerComp(owner);
	owner->AddComponent<PlayerComp>(static_cast<BaseComponent*>(p));
	return p;
}
