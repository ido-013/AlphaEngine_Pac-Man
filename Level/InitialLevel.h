#pragma once
#include <vector>
#include "BaseLevel.h"
#include "../GameObject/GameObject.h"

namespace level
{
	class InitialLevel: public GSM::BaseLevel
	{
	private:
		std::vector<GameObject*> players;
		std::vector<GameObject*> walls;
		std::vector<GameObject*> coins;
		std::vector<GameObject*> enemies;

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}