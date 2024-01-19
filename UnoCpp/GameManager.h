#pragma once
#include <memory>

class TurnHandler;
class DeckManager;
class PlayersManager;
class GameManager
{
private:
	std::shared_ptr<TurnHandler> _turnHandler;
	std::shared_ptr<DeckManager> _deckManager;
	std::shared_ptr<PlayersManager> _playersManager;

	const int MIN_PLAYERS_AMOUNT = 2;
	const int MAX_PLAYERS_AMOUNT = 8;

	void Awake();
	int InitializeGame();
	void WaitPlayerInputToStart();
	void AskForPlayerAmount();
	void CreatePlayers(int amount);
	void RandomizeFirstPlayer();
	void StartGame();
	int GameLoop();
	int AskForRestartOrQuit();
	void RestartGame();
	int QuitGame();

public:
	int EntryPoint();
};

