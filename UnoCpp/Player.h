#pragma once
#include <list>
#include "BaseCard.h"
class Player
{
private:
	std::list<BaseCard> cardsInHand;

public:
	void StartTurn();
	void DrawCards();
	void ShowActions();
	bool HasValidActions();
	void ValidateCardCount();
	void DispatchWinCondition();
};

