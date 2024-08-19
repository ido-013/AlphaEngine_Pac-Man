#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"

GameObject::GameObject() : component()
{
	GameObjectManager::GetGOMPtr()->AddObject(this);
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
