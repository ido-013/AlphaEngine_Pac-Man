#pragma once
#include "BaseLevel.h"
#include "AEEngine.h"
#include "../Components/PlayerComp.h"

using json = nlohmann::ordered_json;

namespace level
{
	class GameClear : public GSM::BaseLevel
	{
	private:
		s8 pFont;
		int score;
		int highScore = 0;
		bool newRecord = false;

	public:
		GameClear(int _score) : score(_score), pFont(NULL) {}

		void Init() override;
		void Update() override;
		void Exit() override;

		friend PlayerComp;
	};
}
