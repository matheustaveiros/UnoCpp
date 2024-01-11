#pragma once
#include <list>
#include "BaseAction.h"
#include "Player.h"
class TurnHandler
{
private:
	int gameDirection;
	int currentPlayerIndex;
	bool gameIsRunning;
	std::list<BaseAction> actionQueue;
	std::list<Player> players;
public:
	int GetGameDirection();
	void TurnLoop();
	void AddActionInQueue(BaseAction& action);
	void ExecuteActionInQueue();
	void StartCurrentPlayerTurn();
	bool IsGameRunning();
};

