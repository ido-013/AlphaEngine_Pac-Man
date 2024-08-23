#pragma once
#include "Event.h"

struct DeathEvent : public Event
{
	DeathEvent(Entity* _src, Entity* _dst) : Event(_src, _dst) {}
};