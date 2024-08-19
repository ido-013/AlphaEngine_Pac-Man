#pragma once
#include "BaseLevel.h"

namespace level
{
	class TransformTest : public GSM::BaseLevel
	{
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}