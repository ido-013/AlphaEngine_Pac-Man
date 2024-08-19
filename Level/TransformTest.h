#pragma once
#include "BaseLevel.h"

namespace Levels
{
	class TransformTest : public GSM::BaseLevel
	{
	public:
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}