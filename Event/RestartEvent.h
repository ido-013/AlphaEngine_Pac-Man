#pragma once
#include "Event.h"

struct RestartEvent : public Event
{
	RestartEvent(Entity* _src, Entity* _dst) : Event(_src, _dst) {}
};