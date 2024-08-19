// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "GSM/GameStateManger.h"
#include "Level/InitialLevel.h"
#include "Level/TestLevel.h"

// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");

	GSM::GameStateManager* gsm = GSM::GameStateManager::GetGSMPtr();

	// reset the system modules
	AESysReset();

	GSM::GameStateManager::GetGSMPtr()->ChangeLevel(new level::InitialLevel);

	// Game Loop
	while (gsm->ShouldExit() == false && gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Your own update logic goes here
		gsm->Update();

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	gsm->Exit();
	
	GSM::GameStateManager::DeleteGSM();

	// free the system
	AESysExit();
}