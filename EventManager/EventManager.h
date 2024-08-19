#pragma once
#include <iostream>
#include <queue>
#include <list>
#include <map>
#include "../Event/Event.h"
#include "../Event/Entity.h"

class EventManager
{
private:
	//A container for all my events* (queue)
	std::queue<Event*> allEvents;

	//A container to have which entities are registered to which events
	//map of (events, container of entities* (list))
	std::map<std::string, std::list<Entity*>> regEvents;

	//Make singleton
	EventManager();

	//	Remove the compiler defined Copy Constructor and Assignment operator
	EventManager(const EventManager& other) = delete;
	const EventManager& operator=(const EventManager& other) = delete;

	//	Prevent others destroying me
	~EventManager();

	//	Pointer to the exisiting Singleton can be accessed without an obj and from me only
	static EventManager* ptr;

public:
	//Interface:
	//	GetSingleton
	static EventManager* GetEMPtr();

	//	DeleteSingleton
	static void DeleteEM();

	// Add an event (event*) this are pointers to dynamic memory, called as the following: AddEvent(new Event);
	template <typename T>
	void AddEvent(Entity* _owner);

	// template fn:
	//		Register entities to a certain event TYPE
	template <typename T>
	void RegisterEntity(Entity*);

	//		Unregister entities to a certain event TYPE
	template <typename T>
	void UnregisterEntity(Entity*);

	// DispatchAllEvents
	void DispatchAllEvents();

	// delete undispatched events if any on destructor
	void DeleteUndispahchEvent();
};

#include "EventManager.inl"
