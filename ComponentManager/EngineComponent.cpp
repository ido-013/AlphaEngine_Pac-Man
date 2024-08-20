#include "EngineComponent.h"
#include "ComponentManager.h"

EngineComponent::EngineComponent(GameObject* _owner) : BaseComponent(_owner) 
{
	ComponentManager<EngineComponent>::GetPtr()->AddComp(this);
}

EngineComponent::~EngineComponent()
{
	ComponentManager<EngineComponent>::GetPtr()->DelComp(this);
}
