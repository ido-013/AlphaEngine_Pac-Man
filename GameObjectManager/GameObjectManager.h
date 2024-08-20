#pragma once
#include <list>
#include <string>
#include "../GameObject/GameObject.h"

class GameObjectManager
{
private:
	std::list<GameObject*> objects;

	GameObjectManager();
	~GameObjectManager();

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator =(const GameObjectManager&) = delete;

	static GameObjectManager* ptr;

public:
	std::list<GameObject*>& GetAllObjects() { return objects; }

	static GameObjectManager* GetPtr();
	static void DeletePtr();

	void AddObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
};