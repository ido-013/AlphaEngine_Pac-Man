#pragma once
#include "BaseLevel.h"
#include "AEEngine.h"

namespace level
{
	class GameOver : public GSM::BaseLevel
	{
	private:
		s8 pFont;
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
