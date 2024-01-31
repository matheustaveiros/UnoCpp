#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Cards/BaseCard.h"
#include "Core/TurnHandler.h"

class BaseCard;
class TurnHandler;
class Player
{
protected:
	std::shared_ptr<TurnHandler> _turnHandler;

private:
	std::vector<std::shared_ptr<BaseCard>> _cardsInHand;
	bool _inUnoState = false;
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
	bool HasValidCardWithSymbolInHand();
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
	void SetUnoState(bool unoState);
	const std::vector<std::shared_ptr<BaseCard>>& GetCards() const;
	const std::shared_ptr<BaseCard>& GetCard(int index) const;
	void CleanPlayerHand();
	void ReplaceCardsInHand(const std::vector<std::shared_ptr<BaseCard>>& cards);
	const std::string& GetName() const;
};

