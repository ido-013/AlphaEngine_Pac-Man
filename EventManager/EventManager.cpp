#include "EventManager.h"
#include <iostream>

EventManager* EventManager::ptr = nullptr;

EventManager::EventManager() {}

EventManager::~EventManager() {}

EventManager* EventManager::GetPtr()
{
    if (ptr == nullptr)
    {
        ptr = new EventManager;
    }

    return ptr;
}

void EventManager::DeletePtr()
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

void EventManager::DispatchAllEvents()
{
    while (!allEvents.empty())
    {
        allEvents.front()->DispatchEvent();
        delete allEvents.front();
        allEvents.pop();
    }
}

void EventManager::DeleteUndispahchEvent()
{
    while (!allEvents.empty())
    {
        delete allEvents.front();
        allEvents.pop();
    }
}
