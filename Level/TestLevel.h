#pragma once
#include "BaseLevel.h"
#include "../GameObject/GameObject.h"

namespace level
{
	class TestLevel : public GSM::BaseLevel
	{
	private:

	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}