#pragma once
#include "BaseLevel.h"
#include "../GameObject/GameObject.h"

namespace level
{
	class InitialLevel: public GSM::BaseLevel
	{
	private:
		int counter{ 0 };
		GameObject* player;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}