#pragma once
#include <vector>
#include "BaseCard.h"
#include <memory>
class Player
{
private:
	std::vector<BaseCard> _cardsInHand;
	const int YELL_UNO_OPTION_INDEX = 99999;
	bool _inUnoState;

	std::shared_ptr<TurnHandler> _turnHandler;

public:
	Player(std::shared_ptr<TurnHandler> turnHandler);

	void StartTurn();
	void DrawCards();
	void ShowActions();
	bool HasValidActions(BaseCard& cardToCompare);
	void ValidateCardCount();
	void DispatchWinCondition();
	void AddCardToHand(BaseCard& card);
	void UseOption(int option);
};

