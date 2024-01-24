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
	bool _inUnoState = false;
	std::shared_ptr<TurnHandler> _turnHandler;
	std::string _name;
	int _yellUnoActionValue = 0;
	int _buyCardActionValue = 0;

public:
	Player(std::shared_ptr<TurnHandler> turnHandler, const std::string& name);

	void StartTurn();
	void DrawTopCardFromDiscardPile();
	void DrawCards() const;
	void ShowExtraActions();
	void WaitForActionInput();
	bool HasValidActions(std::shared_ptr<BaseCard> cardToCompare);
	bool CanWin() const;
	bool CardIsCompatible(std::shared_ptr<BaseCard> card);
	bool CardIsSymbolOnlyCompatible(std::shared_ptr<BaseCard> card);
	void HandleMandatoryPlay();
	void ShowCompatibleOptions();
	void AddCardToHand(std::shared_ptr<BaseCard> card);
	void UseOption(int option);
	void HandleYellUnoOption();
	void HandleBuyCardOption();
	void HandleUseCardOption(int option);
	void DispatchWinCondition();
	void HandleWinCondition(const std::shared_ptr<BaseCard> currentUseCard, int option);
	void HandleCardUsage(const std::shared_ptr<BaseCard> currentUseCard, int option);
	void TurnEnded();
	std::vector<std::shared_ptr<BaseCard>> GetCards() const;
	void CleanPlayerHand();
	void ReplaceCardsInHand(const std::vector<std::shared_ptr<BaseCard>>& cards);
	std::string& GetName();
};

