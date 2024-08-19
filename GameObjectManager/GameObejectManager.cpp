#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::ptr = nullptr;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

GameObjectManager* GameObjectManager::GetGOMPtr()
{
	if (ptr == nullptr)
	{
		ptr = new GameObjectManager;
	}

	return ptr;
}

void GameObjectManager::DeleteGOM()
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

void GameObjectManager::AddObject(GameObject* obj)
{
	objects.push_back(obj);
}

void GameObjectManager::RemoveObject(GameObject* obj)
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (*it == obj)
		{
			objects.erase(it);
			return;
		}
	}
}
