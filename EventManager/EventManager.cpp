#include "EventManager.h"
#include <iostream>

EventManager::EventManager() {}

EventManager::~EventManager() 
{
    DeleteUndispahchEvent();
}

void EventManager::DispatchAllEvents()
{
    while (!allEvents.empty())
    {
        allEvents.front()->DispatchEvent();

        if (allEvents.empty())
            break;

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
