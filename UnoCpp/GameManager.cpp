#include "GameManager.h"

int GameManager::EntryPoint()
{
	Awake();
	return GameLoop();
}

void GameManager::Awake()
{
	turnHandler = TurnHandler();
	deckManager = DeckManager();
}

void GameManager::WaitPlayerInputToStart()
{
	
}

void GameManager::StartGame()
{
	deckManager.CreateDeck();
}

int GameManager::GameLoop()
{
	while (turnHandler.IsGameRunning()) {
		turnHandler.TurnLoop();
	}

	return AskForRestartOrQuit();
}

int GameManager::AskForRestartOrQuit()
{
	//GetInput
	//If restart
	//RestarGame
	//else
	//QuitGame
}

void GameManager::RestartGame()
{
	//call restart of main classes
}

int GameManager::QuitGame()
{
	return 0;
}


