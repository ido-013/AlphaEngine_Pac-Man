#include "LogicComponent.h"
#include "ComponentManager.h"

LogicComponent::LogicComponent(GameObject* _owner) : BaseComponent(_owner)
{
	ComponentManager<LogicComponent>::GetPtr()->AddComp(this);
}

LogicComponent::~LogicComponent()
{
	ComponentManager<LogicComponent>::GetPtr()->DelComp(this);
}
