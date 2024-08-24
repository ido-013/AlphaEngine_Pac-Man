#pragma once
#include "Event.h"

class Entity
{
public:
	enum Type
	{
		None = 0,
		Player = 1,
		Coin = 2,
		Flag = 3,
		Wall = 4,
		Enemy = 5,
		Super = 6,
	};

	virtual void OnEvent(Event* event) = 0;
	void SetType(const Type& _type);
	const Type GetType() const;

private:
	Type type;
};