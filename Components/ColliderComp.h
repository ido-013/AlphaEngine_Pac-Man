#pragma once

#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include "../Event/Entity.h"
#include "../Event/CollisionEvent.h"
#include <list>

class ColliderComp : public EngineComponent, public Entity
{
private:
	std::list<TransformComp*> otherTrans;
	TransformComp* myTrans;
	bool isCollision() const;

public:
	ColliderComp(GameObject* _owner);

	void OnEvent(Event* event) override;
	void Update() override;

	void AddTrans(TransformComp* trans);
	void DelTrans(TransformComp* trans);

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateColliderComponent(GameObject* owner);
	static constexpr const char* TypeName = "ColliderComp";
};