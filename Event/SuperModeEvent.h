#pragma once
#include "Event.h"

struct SuperModeEvent : public Event
{
	SuperModeEvent(Entity* _src, Entity* _dst) : Event(_src, _dst) {}
};