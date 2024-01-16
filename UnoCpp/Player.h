#pragma once
#include "BaseCard.h"
#include "TurnHandler.h"
#include <vector>
#include <memory>
#include <string>

class BaseCard;
class TurnHandler;
class Player
{
private:
	std::vector<std::shared_ptr<BaseCard>> _cardsInHand;
	const int YELL_UNO_OPTION_INDEX = 99999;
	bool _inUnoState;
	std::string _name;

	std::shared_ptr<TurnHandler> _turnHandler;

public:
	Player(std::shared_ptr<TurnHandler> turnHandler, std::string name);

	void StartTurn();
	void DrawCards();
	void ShowActions();
	bool HasValidActions(std::shared_ptr<BaseCard> cardToCompare);
	void ValidateCardCount();
	void DispatchWinCondition();
	void AddCardToHand(std::shared_ptr<BaseCard> card);
	void UseOption(int option);
	std::vector<std::shared_ptr<BaseCard>> GetCards();
	void CleanPlayerHand();
	std::string& GetName();
};

