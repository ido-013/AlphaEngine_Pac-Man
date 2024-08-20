#include "GraphicComponent.h"
#include "ComponentManager.h"

GraphicComponent::GraphicComponent(GameObject* _owner) : BaseComponent(_owner) 
{
	ComponentManager<GraphicComponent>::GetPtr()->AddComp(this);
}

GraphicComponent::~GraphicComponent()
{
	ComponentManager<GraphicComponent>::GetPtr()->DelComp(this);
}
