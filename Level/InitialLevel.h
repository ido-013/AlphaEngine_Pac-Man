#pragma once
#include <vector>
#include "BaseLevel.h"
#include "../GameObject/GameObject.h"

extern const int windowWidth;
extern const int windowHeight;

namespace level
{
	class InitialLevel: public GSM::BaseLevel
	{
	private:
		int playerMapPos[2];
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