#pragma once
#include "BaseCard.h"
#include "TurnHandler.h"
#include <vector>
#include <memory>

class BaseCard;
class TurnHandler;
class Player
{
private:
	std::vector<std::shared_ptr<BaseCard>> _cardsInHand;
	const int YELL_UNO_OPTION_INDEX = 99999;
	bool _inUnoState;

	std::shared_ptr<TurnHandler> _turnHandler;

public:
	Player(std::shared_ptr<TurnHandler> turnHandler);

	void StartTurn();
	void DrawCards();
	void ShowActions();
	bool HasValidActions(std::shared_ptr<BaseCard> cardToCompare);
	void ValidateCardCount();
	void DispatchWinCondition();
	void AddCardToHand(std::shared_ptr<BaseCard> card);
	void UseOption(int option);
};

