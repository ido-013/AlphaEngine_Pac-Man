#pragma once
#include <map>
#include <string>
#include "AEEngine.h"
#include "../ComponentManager/GraphicComponent.h"
#include "../Components/SpriteComp.h"
#include "../Animation/Animation.h"

class AnimatorComp : public GraphicComponent
{
private:
	bool loop;
	float speed;
	Animation* animation;

public:
	AnimatorComp(GameObject* _owner);

	void SetAnimation(bool _loop, float _speed, std::string _name);
	void Update() override;
};