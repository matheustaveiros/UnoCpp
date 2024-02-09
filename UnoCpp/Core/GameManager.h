#pragma once
#include <memory>
#include "Player/PlayersManager.h"
#include "Deck/DeckManager.h"
#include "TurnHandler.h"
class GameManager
{
private:
	std::unique_ptr<TurnHandler> _turnHandler;
	std::unique_ptr<DeckManager> _deckManager;
	std::unique_ptr<PlayersManager> _playersManager;

	const int MIN_PLAYERS_AMOUNT = 2;
	const int MAX_PLAYERS_AMOUNT = 8;

	void Awake();
	int InitializeGame();
	void WaitPlayerInputToStart() const;
	void AskForPlayerAmount();
	void AskForBotAmount();
	void CreatePlayers(int amount);
	void CreateBots(int amount);
	void RandomizeFirstPlayer();
	void StartGame();
	int GameLoop();
	int AskForRestartOrQuit();
	void RestartGame();
	int QuitGame() const;

public:
	int EntryPoint();
};

