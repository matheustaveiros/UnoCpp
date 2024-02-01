#include <iostream>
#include <windows.h>
#include "Deck/DeckManager.h"
#include "Console/ConsoleHelper.h"
#include "Console/GameInstructionsHandler.h"
#include "Utils/RandomHelper.h"
#include "Player/Player.h"
#include "Console/UnoLogo.h"
#include "TurnHandler.h"
#include "GameManager.h"

int GameManager::EntryPoint()
{
	ConsoleHelper::SetDisplayLevel(Enums::DisplayLevel::Developer);
	UnoLogo::PrintLogo();
	GameInstructionsHandler::DrawInstructions();

	Awake();
	return InitializeGame();
}

int GameManager::InitializeGame()
{
	WaitPlayerInputToStart();
	AskForPlayerAmount();
	AskForBotAmount();
	RandomizeFirstPlayer();
	StartGame();
	return GameLoop();
}

void GameManager::Awake()
{
	RandomHelper::Seed();

	_playersManager = std::make_shared<PlayersManager>();
	_deckManager = std::make_shared<DeckManager>();
	_turnHandler = std::make_shared<TurnHandler>();
	_playersManager->Initialize(_turnHandler, _deckManager);
	_deckManager->Initialize(_turnHandler, _playersManager);
	_turnHandler->Initialize(_deckManager, _playersManager);

	_deckManager->CreateDeck();
}

void GameManager::WaitPlayerInputToStart() const
{
	ConsoleHelper::WaitForAnyKey("Press Any Key to Start The Game\n");
	ConsoleHelper::Clear();
}

void GameManager::AskForPlayerAmount()
{
	int amount = 0;
	while (amount < MIN_PLAYERS_AMOUNT || amount > MAX_PLAYERS_AMOUNT)
	{
		amount = ConsoleHelper::GetInput<int>(std::format("Type the number of players: (min {}, max {})\n", MIN_PLAYERS_AMOUNT, MAX_PLAYERS_AMOUNT));
	}

	CreatePlayers(amount);
}

void GameManager::AskForBotAmount()
{
	int maxAmount = MAX_PLAYERS_AMOUNT - static_cast<int>(_playersManager->GetPlayers().size());
	int amount = -1;
	while (amount == -1 || amount > maxAmount)
	{
		amount = ConsoleHelper::GetInput<int>(std::format("Type the number of [BOT] Players: (min {}, max {})\n", 0, maxAmount));
	}

	CreateBots(amount);
}

void GameManager::CreatePlayers(int amount)
{
	std::vector<std::string> playerNames;
	for (int i = 0; i < amount; i++)
	{
		std::string playerName = ConsoleHelper::GetInput<std::string>(std::format("Insert Player {} Name\n", i + 1));
		playerNames.emplace_back(playerName);
	}

	_playersManager->CreatePlayers(amount, playerNames);
}

void GameManager::CreateBots(int amount)
{
	std::vector<std::string> botNames;
	for (int i = 0; i < amount; i++)
	{
		std::string botName = ConsoleHelper::GetInput<std::string>(std::format("Insert Bot {} Name\n", i + 1));
		botNames.emplace_back("[AI] " + botName);
	}

	_playersManager->CreateBots(amount, botNames);
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

	ConsoleHelper::PrintMessage("Game Starting...\n");
	Sleep(1000);
	ConsoleHelper::Clear();

	_turnHandler->SetGameState(true);
}

int GameManager::GameLoop()
{
	while (_turnHandler->IsGameRunning())
	{
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

int GameManager::QuitGame() const
{
	return 0;
}


;