#include "GameManager.h"

int GameManager::EntryPoint()
{
	Awake();
	return GameLoop();
}

void GameManager::Awake()
{
	_deckManager = DeckManager();
	_turnHandler = TurnHandler(_deckManager);
}

void GameManager::WaitPlayerInputToStart()
{
	
}

void GameManager::StartGame()
{
	_deckManager.CreateDeck();
}

int GameManager::GameLoop()
{
	while (_turnHandler.IsGameRunning()) {
		_turnHandler.TurnLoop();
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


