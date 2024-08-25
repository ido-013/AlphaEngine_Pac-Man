#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Event/CollisionEvent.h"
#include "../Event/DestroyEvent.h"
#include "../Event/DeathEvent.h"
#include "../Event/SuperModeEvent.h"
#include "../Event/RestartEvent.h"
#include "../Components/PlayerComp.h"
#include "../Components/EnemyComp.h"
#include "../Components/AudioComp.h"
#include "../EventManager/EventManager.h"

GameObject::GameObject() : component()
{
	GameObjectManager::GetInstance().AddObject(this);
	EventManager::GetInstance().AddEntity(this);
}

GameObject::~GameObject()
{
	for (auto it : component)
	{
		if (it.second)
			delete it.second;	
	}

	component.clear();
	EventManager::GetInstance().RemoveEntity(this);
}

void GameObject::OnEvent(Event* event)
{
	if (GetType() == Entity::Player)
	{
		if (dynamic_cast<CollisionEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Coin)
			{
				GetComponent<AudioComp>()->playAudio(0, "Assets/Audio/dropping-coin.mp3");
				EventManager::GetInstance().AddEvent<DestroyEvent>(event->dst, event->src);
				GetComponent<PlayerComp>()->AddScore(10, false);
				GetComponent<PlayerComp>()->UpdateCoin();
			}

			if (event->src->GetType() == Entity::SuperCoin)
			{
				GetComponent<AudioComp>()->playAudio(0, "Assets/Audio/coin-flip.mp3");
				EventManager::GetInstance().AddEvent<DestroyEvent>(event->dst, event->src);
				GetComponent<PlayerComp>()->AddScore(100, false);
				GetComponent<PlayerComp>()->UpdateCoin();
			}

			else if (event->src->GetType() == Entity::Super)
			{
				GetComponent<AudioComp>()->playAudio(0, "Assets/Audio/ore.mp3");
				EventManager::GetInstance().AddEvent<DestroyEvent>(event->dst, event->src);
				EventManager::GetInstance().AddEvent<SuperModeEvent>(event->dst, Entity::Enemy);
			}

			else if (event->src->GetType() == Entity::Ghost)
			{
				GetComponent<PlayerComp>()->AddScore(500, true);
			}
		}
	}

	else if (GetType() == Entity::Coin)
	{
		if (dynamic_cast<DestroyEvent*>(event) != nullptr)
		{
			GameObjectManager::GetInstance().RemoveObject(this);

		}
	}

	else if (GetType() == Entity::SuperCoin)
	{
		if (dynamic_cast<DestroyEvent*>(event) != nullptr)
		{
			GameObjectManager::GetInstance().RemoveObject(this);
		}
	}

	else if (GetType() == Entity::Super)
	{
		if (dynamic_cast<DestroyEvent*>(event) != nullptr)
		{
			GameObjectManager::GetInstance().RemoveObject(this);
		}
	}

	else if (GetType() == Entity::Enemy)
	{
		if (dynamic_cast<SuperModeEvent*>(event) != nullptr)
		{
			GetComponent<EnemyComp>()->InitGhost();
		}

		if (dynamic_cast<RestartEvent*>(event) != nullptr)
		{
			this->SetType(Entity::Enemy);
			GetComponent<EnemyComp>()->ResetPos();
		}

		if (dynamic_cast<CollisionEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Player)
			{
				EventManager::GetInstance().AddEvent<DeathEvent>(event->dst, event->src);
				event->src->SetType(Entity::None);
			}
		}
	}

	else if (GetType() == Entity::None)
	{
		if (dynamic_cast<DeathEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Enemy)
			{
				EventManager::GetInstance().AddEvent<RestartEvent>(event->dst, Entity::Enemy);
				EventManager::GetInstance().AddEvent<RestartEvent>(event->dst, Entity::Ghost);
				EventManager::GetInstance().AddEvent<RestartEvent>(event->dst, Entity::Specter);
				this->SetType(Entity::Player);
				GetComponent<PlayerComp>()->UpdateLife();
			}
		}
	}

	else if (GetType() == Entity::Ghost)
	{
		if (dynamic_cast<RestartEvent*>(event) != nullptr)
		{
			this->SetType(Entity::Enemy);
			GetComponent<EnemyComp>()->ResetPos();
		}

		if (dynamic_cast<CollisionEvent*>(event) != nullptr)
		{
			if (event->src->GetType() == Entity::Player)
			{
				GetComponent<EnemyComp>()->InitSpector();
			}
		}
	}

	else if (GetType() == Entity::Specter)
	{
		if (dynamic_cast<RestartEvent*>(event) != nullptr)
		{
			this->SetType(Entity::Enemy);
			GetComponent<EnemyComp>()->ResetPos();
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
