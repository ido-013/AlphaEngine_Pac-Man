#include "EventManager.h"
#include <iostream>

EventManager* EventManager::ptr = nullptr;

EventManager::EventManager() {}

EventManager::~EventManager() {}

EventManager* EventManager::GetEMPtr()
{
    if (ptr == nullptr)
    {
        ptr = new EventManager;
    }

    return ptr;
}

void EventManager::DeleteEM()
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
        auto it = regEvents.find(allEvents.front()->name);

        if (it != regEvents.end())
        {
            for (auto entity : it->second)
            {
                entity->OnEvent(allEvents.front());
            }
        }

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
