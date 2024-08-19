#include "GraphicComponent.h"
#include "ComponentManager.h"

GraphicComponent::GraphicComponent(GameObject* _owner) : BaseComponent(_owner) 
{
	ComponentManager<GraphicComponent>::GetCMPtr()->AddComp(this);
}

GraphicComponent::~GraphicComponent()
{
	ComponentManager<GraphicComponent>::GetCMPtr()->DelComp(this);
}
