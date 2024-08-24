#pragma once
#include "BaseLevel.h"
#include "../GameObject/GameObject.h"

namespace level
{
	class InitialLevel: public GSM::BaseLevel
	{
	private:
		GameObject* player = nullptr;
		GameObject* enemies[4];
		int coinCount = 0;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}