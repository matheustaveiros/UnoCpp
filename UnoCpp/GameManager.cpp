#include "GameManager.h"
#include "TurnHandler.h"
#include "DeckManager.h"
#include <iostream>
#include "ConsoleHelper.h"
#include "RandomHelper.h"
#include "Player.h"

int GameManager::EntryPoint()
{
	ConsoleHelper::SetDisplayLevel(Enums::DisplayLevel::Developer);

	Awake();
	return InitializeGame();
}

int GameManager::InitializeGame()
{
	WaitPlayerInputToStart();
	AskForPlayerAmount();
	RandomizeFirstPlayer();
	StartGame();
	return GameLoop();
}

void GameManager::Awake()
{
	RandomHelper::Seed();

	_playersManager = std::make_shared<PlayersManager>();
	_deckManager = std::make_shared<DeckManager>(_playersManager);
	_turnHandler = std::make_shared<TurnHandler>(_deckManager, _playersManager);
	_playersManager->Initialize(_turnHandler, _deckManager);
	_deckManager->Initialize(_turnHandler);

	_deckManager->CreateDeck();
}

void GameManager::WaitPlayerInputToStart()
{
	ConsoleHelper::WaitForAnyKey("Press Any Key to Start The Game\n");
}

void GameManager::AskForPlayerAmount()
{
	int amount = 0;
	while (amount < MIN_PLAYERS_AMOUNT || amount > MAX_PLAYERS_AMOUNT)
	{
		amount = ConsoleHelper::GetInput<int>("Type the number of players: (min " + 
			std::to_string(MIN_PLAYERS_AMOUNT) + ", max " + std::to_string(MAX_PLAYERS_AMOUNT) + ")\n");
	}

	CreatePlayers(amount);
}

void GameManager::CreatePlayers(int amount)
{
	std::vector<std::string> playerNames;
	for (int i = 0; i < amount; i++)
	{
		std::string playerName = ConsoleHelper::GetInput<std::string>("Insert Player " + std::to_string(i + 1) + " Name: \n");
		playerNames.push_back(playerName);
	}

	_playersManager->CreatePlayers(amount, playerNames);
}

void GameManager::RandomizeFirstPlayer()
{
	int playersSize = static_cast<int>(_playersManager->GetPlayers().size()) - 1;
	int selectedPlayer = RandomHelper::Range(0, playersSize);
	_turnHandler->SetStarterPlayerOrder(selectedPlayer);

	ConsoleHelper::PrintMessage("Player Randomly Selected: " + _playersManager->GetPlayer(selectedPlayer)->GetName() + "\n");
}

void GameManager::StartGame()
{
	_playersManager->GiveFirstCardsToPlayers();
	_turnHandler->ThrowCardFromDeckToDiscardPile(true);
	_turnHandler->SetGameState(true);
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
	int selection = ConsoleHelper::GetInput<int>("Press 1 to Play Again the Game\nPress 2 to Leave the Game\n");
	if (selection == 1)
	{
		RestartGame();
	}
	else if (selection == 2)
	{
		return QuitGame();
	}
	else
	{
		ConsoleHelper::PrintMessage("Invalid Option, Please Type a Valid Option");
		return AskForRestartOrQuit();
	}

	return 0;
}

void GameManager::RestartGame()
{
	_deckManager->ResetAllCards();
	_playersManager->DestroyAllPlayers();
	_turnHandler->ResetState();
	ConsoleHelper::Clear();
	InitializeGame();
}

int GameManager::QuitGame()
{
	return 0;
}


