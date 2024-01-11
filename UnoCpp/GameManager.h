#pragma once
#include "DeckManager.h"
#include "TurnHandler.h"
class GameManager
{
private:
	TurnHandler turnHandler;
	DeckManager deckManager;

	void Awake();
	void WaitPlayerInputToStart();
	void StartGame();
	int GameLoop();
	int AskForRestartOrQuit();
	void RestartGame();
	int QuitGame();

public:
	int EntryPoint();
};

