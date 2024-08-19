#pragma once
#include <string>

class Entity;

struct Event
{
	Event(std::string _name, Entity* _owner);
	virtual ~Event() = default;
	
	Entity* owner;
	std::string name;
};