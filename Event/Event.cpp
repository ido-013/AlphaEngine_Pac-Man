#include "Event.h"
#include "Entity.h"

Event::Event(std::string _name, Entity* _owner) : name(_name), owner(_owner)
{
}
