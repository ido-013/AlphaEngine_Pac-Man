#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Event/CollisionEvent.h"
#include "../Event/DestroyEvent.h"
#include "../Event/DeathEvent.h"
#include "../Components/PlayerComp.h"
#include "../Components/EnemyComp.h"
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

			if (event->src->GetType() == Entity::Super)
			{
				GetComponent<PlayerComp>()->superMode = true;
				EventManager::GetInstance().AddEvent<DestroyEvent>(event->dst, event->src);
			}

			if (event->src->GetType() == Entity::Enemy)
			{
				if (GetComponent<PlayerComp>()->superMode)
				{
					GetComponent<PlayerComp>()->AddScore(500);
					EventManager::GetInstance().AddEvent<DeathEvent>(event->dst, event->src);
				}
				else
				{
					EventManager::GetInstance().AddEvent<DeathEvent>(event->src, event->dst);
				}
			}
		}

		if (dynamic_cast<DeathEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Enemy)
			{
				GetComponent<PlayerComp>()->AddLife(-1);
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

	if (GetType() == Entity::Super)
	{
		if (dynamic_cast<DestroyEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Player)
			{
				GameObjectManager::GetInstance().RemoveObject(this);
			}
		}
	}

	if (GetType() == Entity::Enemy)
	{
		if (dynamic_cast<DeathEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Player)
			{
				GetComponent<EnemyComp>()->ResetPos();
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
