#include "GameClear.h"

#include <iostream>
#include <fstream>
#include "json.hpp"
#include "../GSM/GameStateManager.h"
#include "../Level/InitialLevel.h"


void level::GameClear::Init() 
{
	pFont = AEGfxCreateFont("Assets/Arial-Italic.ttf", 60);

	std::fstream file;
	file.open("highscore.json", std::fstream::in);

	if (!file.is_open())
		throw std::invalid_argument("level::GameClear::Init Invalid filename highscore.json");

	json data;
	file >> data;

	auto it = data.find("highScore");
	highScore = it.value();

	if (highScore < score)
	{
		highScore = score;
		newRecord = true;
	}
}

void level::GameClear::Update()
{
	std::string scoreText = "Your Score: " + std::to_string(score);
	std::string highScoreText = "High Score: " + std::to_string(highScore) + (newRecord ? " (NEW!)" : "");

	AEGfxPrint(pFont, "Game Clear", -0.95f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f);
	AEGfxPrint(pFont, scoreText.c_str(), -0.9f, -0.2f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	AEGfxPrint(pFont, highScoreText.c_str(), -0.9f, -0.3f, 0.5f, 1.f, 1.f, 1.f, 1.f);
	AEGfxPrint(pFont, "Click Left Button to Restart", -0.9f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f);

	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new level::InitialLevel);
	};
}

void level::GameClear::Exit()
{
	AEGfxDestroyFont(pFont);

	json data;

	std::fstream file;
	file.open("highscore.json", std::fstream::out);

	data["highScore"] = highScore;

	if (!file.is_open())
		throw std::invalid_argument("level::GameClear::Exit file write error highscore.json");

	file << std::setw(2) << data;

	file.close();
}

