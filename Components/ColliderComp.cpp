#include "ColliderComp.h"

bool ColliderComp::isCollision() const
{
	if (otherTrans.empty()) return false;

	double aX = myTrans->GetPos().x;
	double aY = myTrans->GetPos().y;
	double aW = myTrans->GetScale().x / 2;
	double aH = myTrans->GetScale().y / 2;
	
	for (auto it : otherTrans)
	{
		double bX = it->GetPos().x;
		double bY = it->GetPos().y;
		double bW = it->GetScale().x / 2;
		double bH = it->GetScale().y / 2;
		
		if (aX - aW > bX + bW) return false;
		if (bX - bW > aX + aW) return false;
		if (aY - aH > bY + bH) return false;
		if (bY - bH > aY + aH) return false;
	}

	return true;
}

ColliderComp::ColliderComp(GameObject* _owner) : EngineComponent(_owner), myTrans(_owner->GetComponent<TransformComp>()) {}

void ColliderComp::OnEvent(Event* event)
{

}

void ColliderComp::Update()
{
	if (isCollision())
	{
		EventManager::GetEMPtr()->AddEvent<CollisionEvent>(this);
	}
}

void ColliderComp::AddTrans(TransformComp* trans)
{
	otherTrans.push_back(trans);
}

void ColliderComp::DelTrans(TransformComp* trans)
{
	for (auto it = otherTrans.begin(); it != otherTrans.end(); it++)
	{
		if (*it == trans)
		{
			otherTrans.erase(it);
			break;
		}
	}
}

void ColliderComp::LoadFromJson(const json&)
{
}

json ColliderComp::SaveToJson()
{
	return json();
}

BaseRTTI* ColliderComp::CreateColliderComponent(GameObject* owner)
{
	return nullptr;
}