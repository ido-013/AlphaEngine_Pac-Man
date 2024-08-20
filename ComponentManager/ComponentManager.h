#pragma once
#include <list>

/////////////Manager class//////////////
//
//Manage components of a certain type (Logic, Engine, Graphics)
//
//Only 1 manager of a certain type cna exist at a time (Singleton)
//
//Updates ALL COMPONENTS of a certain type
//	- Whenever a component of a certain type is created, add it to the manager
//
//Container for the components!
//
//////////////////////////

template <typename T>
class ComponentManager
{
private:
	ComponentManager();
	ComponentManager(const ComponentManager& other) = delete;
	const ComponentManager& operator=(const ComponentManager& other) = delete;
	~ComponentManager();

	static ComponentManager* ptr;

	std::list<T*> component;

public:
	static ComponentManager* GetPtr();
	static void DeletePtr();

	void AddComp(T* comp);
	void DelComp(T* comp);

	void Update();
};

#include "ComponentManager.inl"
