#pragma once
#include "BaseLevel.h"

namespace level
{
	class GameOver : public GSM::BaseLevel
	{
	private:

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}
