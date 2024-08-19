#pragma once
#include "Event.h"

struct CollisionEvent : public Event
{
	CollisionEvent(Entity* _owner) : Event("struct CollisionEvent", _owner) {}
};