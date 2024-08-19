#include "CollisionManager.h"
#include "AEEngine.h"

CollisionManager* CollisionManager::ptr = nullptr;

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager()
{

}

bool CollisionManager::isCollision(TransformComp* a, TransformComp* b) const
{
	double aX = a->GetPos().x;
	double aY = a->GetPos().y;
	double aW = a->GetScale().x / 2;
	double aH = a->GetScale().y / 2;

	double bX = b->GetPos().x;
	double bY = b->GetPos().y;
	double bW = b->GetScale().x / 2;
	double bH = b->GetScale().y / 2;

	if (aX - aW > bX + bW) return false;
	if (bX - bW > aX + aW) return false;
	if (aY - aH > bY + bH) return false;
	if (bY - bH > aY + aH) return false;

	return true;
}

CollisionManager* CollisionManager::GetPtr()
{
    if (ptr == nullptr)
    {
        ptr = new CollisionManager;
    }

    return ptr;
}

void CollisionManager::DeletePtr()
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

void CollisionManager::AddTrans(TransformComp* trans)
{
	transformList.push_back(trans);
}

void CollisionManager::DelTrans(TransformComp* trans)
{
	for (auto it = transformList.begin(); it != transformList.end(); it++)
	{
		if (*it == trans)
		{
			transformList.erase(it);
			break;
		}
	}
}

void CollisionManager::Update()
{
	EventManager* em = EventManager::GetPtr();

	for (int i = 0; i < transformList.size() - 1; i++)
	{
		for (int j = i + 1; j < transformList.size(); j++)
		{
			TransformComp* a = transformList[i];
			TransformComp* b = transformList[j];

			if (isCollision(a, b))
			{
				em->AddEvent<CollisionEvent>(a->GetOwner(), b->GetOwner());
				em->AddEvent<CollisionEvent>(b->GetOwner(), a->GetOwner());
			}
		}
	}
}
