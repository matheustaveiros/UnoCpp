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

