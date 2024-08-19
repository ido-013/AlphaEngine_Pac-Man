#pragma once
#include <vector>
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include "../Event/CollisionEvent.h"

class CollisionManager
{
private:
	CollisionManager();

	CollisionManager(const CollisionManager& other) = delete;
	const CollisionManager& operator=(const CollisionManager& other) = delete;
	~CollisionManager();

	static CollisionManager* ptr;

	std::vector<TransformComp*> transformList;

	bool isCollision(TransformComp*, TransformComp*) const;

public:
	static CollisionManager* GetPtr();
	static void DeletePtr();
	void AddTrans(TransformComp* trans);
	void DelTrans(TransformComp* trans);

	void Update();
};