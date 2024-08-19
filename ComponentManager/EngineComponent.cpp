#include "EngineComponent.h"
#include "ComponentManager.h"

EngineComponent::EngineComponent(GameObject* _owner) : BaseComponent(_owner) 
{
	ComponentManager<EngineComponent>::GetCMPtr()->AddComp(this);
}

EngineComponent::~EngineComponent()
{
	ComponentManager<EngineComponent>::GetCMPtr()->DelComp(this);
}
