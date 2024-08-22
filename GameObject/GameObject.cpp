#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Event/CollisionEvent.h"
#include "../Event/DestroyEvent.h"
#include "../Components/PlayerComp.h"
#include "../EventManager/EventManager.h"

GameObject::GameObject() : component()
{
	GameObjectManager::GetInstance().AddObject(this);
}

GameObject::~GameObject()
{
	for (auto it : component)
	{
		if (it.second)
			delete it.second;	
	}

	component.clear();
}

void GameObject::OnEvent(Event* event)
{
	if (GetType() == Entity::Player)
	{
		if (dynamic_cast<CollisionEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Coin)
			{
				GetComponent<PlayerComp>()->AddScore(10);
				EventManager::GetInstance().AddEvent<DestroyEvent>(event->dst, event->src);
			}
		}
	}

	if (GetType() == Entity::Coin)
	{
		if (dynamic_cast<DestroyEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Player)
			{
				GameObjectManager::GetInstance().RemoveObject(this);
			}
		}
	}
}

BaseComponent* GameObject::GetBase(std::string typeName)
{
	auto it = component.find(typeName);
	if (it != component.end())
	{
		return it->second;
	}

	return nullptr;
}
