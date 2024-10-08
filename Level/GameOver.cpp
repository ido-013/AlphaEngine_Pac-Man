#include "GameOver.h"
#include <iostream>
#include "../GSM/GameStateManager.h"
#include "../Level/InitialLevel.h"

void level::GameOver::Init()
{
	pFont = AEGfxCreateFont("Assets/Arial-Italic.ttf", 60);
}

void level::GameOver::Update()
{
	AEGfxPrint(pFont, "Game Over", -0.95f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f);
	AEGfxPrint(pFont, "Click Left Button to Restart", -0.9f, -0.2f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	
	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new level::InitialLevel);
	};
}

void level::GameOver::Exit()
{
	AEGfxDestroyFont(pFont);
}

