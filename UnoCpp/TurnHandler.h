#pragma once
#include <list>
#include "BaseAction.h"
#include "Player.h"
class TurnHandler
{
private:
	int _gameDirection;
	int _currentPlayerIndex;
	bool _gameIsRunning;
	std::list<BaseAction> _actionQueue;
	std::list<Player> _players;
public:
	int GetGameDirection();
	void TurnLoop();
	void AddActionInQueue(BaseAction& action);
	void ExecuteActionInQueue();
	void StartCurrentPlayerTurn();
	bool IsGameRunning();
};

