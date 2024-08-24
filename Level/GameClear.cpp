#include "GameClear.h"
#include <iostream>
#include "../GSM/GameStateManager.h"
#include "../Level/InitialLevel.h"

void level::GameClear::Init()
{
	pFont = AEGfxCreateFont("Assets/Arial-Italic.ttf", 60);
}

void level::GameClear::Update()
{
	std::string s = "Your Score: " + std::to_string(score);

	AEGfxPrint(pFont, "Game Clear", -0.95f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f);
	AEGfxPrint(pFont, "Click Left Button to Restart", -0.9f, -0.2f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	AEGfxPrint(pFont, s.c_str(), -0.9f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f);

	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new level::InitialLevel);
	};
}

void level::GameClear::Exit()
{
	AEGfxDestroyFont(pFont);
}

