#include "GameManager.h"
#include "TurnHandler.h"
#include "DeckManager.h"
#include <iostream>

int GameManager::EntryPoint()
{
	Awake();
	WaitPlayerInputToStart();
	return GameLoop();
}

void GameManager::Awake()
{
	_playersManager = std::make_shared<PlayersManager>();
	_deckManager = std::make_shared<DeckManager>(_playersManager);
	_turnHandler = std::make_shared<TurnHandler>(_deckManager, _playersManager);
	_playersManager->Initialize(_turnHandler);

	_deckManager->CreateDeck();
}

void GameManager::WaitPlayerInputToStart()
{
	//temp
	std::cout << "Press Any Key to Start The Game";
	std::cin.get();
	StartGame();
}

void GameManager::StartGame()
{
	
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
	//RestartGame
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


