#pragma once
#include "Event.h"

struct DestroyEvent : public Event
{
	DestroyEvent(Entity* _src, Entity* _dst) : Event(_src, _dst) {}
};