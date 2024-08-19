#pragma once
#include <string>
#include <list>
#include "../GameObject/GameObject.h"

class Prefab
{
private:
	std::string name;
	std::list<BaseComponent*> component;

public:
	Prefab(GameObject*);
	void SavePrefab(const std::string& filename);
	Prefab* LoadPrefab(const std::string& filename);
};