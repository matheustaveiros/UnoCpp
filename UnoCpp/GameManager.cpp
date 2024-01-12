#include "GameManager.h"
#include "TurnHandler.h"
#include "DeckManager.h"

int GameManager::EntryPoint()
{
	Awake();
	return GameLoop();
}

void GameManager::Awake()
{
	_deckManager = std::make_shared<DeckManager>();
	_turnHandler = std::make_shared<TurnHandler>(_deckManager);
}

void GameManager::WaitPlayerInputToStart()
{
	
}

void GameManager::StartGame()
{
	_deckManager->CreateDeck();
}

int GameManager::GameLoop()
{
	while (_turnHandler->IsGameRunning()) {
		_turnHandler->TurnLoop();
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

	return 0;
}

void GameManager::RestartGame()
{
	//call restart of main classes
}

int GameManager::QuitGame()
{
	return 0;
}


