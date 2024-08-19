#include "LogicComponent.h"
#include "ComponentManager.h"

LogicComponent::LogicComponent(GameObject* _owner) : BaseComponent(_owner)
{
	ComponentManager<LogicComponent>::GetCMPtr()->AddComp(this);
}

LogicComponent::~LogicComponent()
{
	ComponentManager<LogicComponent>::GetCMPtr()->DelComp(this);
}
