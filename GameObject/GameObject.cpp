#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Event/CollisionEvent.h"

GameObject::GameObject() : component()
{
	GameObjectManager::GetPtr()->AddObject(this);
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
