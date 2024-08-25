#pragma once
#include "Event.h"

class Entity
{
public:
	enum Type
	{
		None,
		Wall,
		Player,
		Coin,
		SuperCoin,
		Super,
		Enemy,
		Ghost,
		Specter,
	};

	virtual void OnEvent(Event* event) = 0;
	void SetType(const Type& _type);
	const Type GetType() const;

private:
	Type type;
};