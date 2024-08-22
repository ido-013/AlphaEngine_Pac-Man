#pragma once
#include "Event.h"

class Entity
{
public:
	enum Type
	{
		Player = 0,
		Coin = 1,
		Flag = 2,
		Wall = 3,
		Enemy = 4,
	};

	virtual void OnEvent(Event* event) = 0;
	void SetType(const Type& _type);
	const Type GetType() const;

private:
	Type type;
};