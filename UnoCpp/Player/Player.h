#pragma once
#include <vector>
#include <memory>
#include <string>
#include <format>
#include "Cards/BaseCard.h"
#include "Core/TurnHandler.h"
#include "Console/ConsoleHelper.h"
#include "Console/CardDrawHelper.h"

class BaseCard;
class TurnHandler;
class Player
{
protected:
	std::shared_ptr<TurnHandler> _turnHandler;

	void DrawTopCardFromDiscardPile();
	bool CardIsCompatible(std::shared_ptr<BaseCard> card);
	bool CardIsSymbolOnlyCompatible(std::shared_ptr<BaseCard> card);
	void HandleYellUnoOption();
	void HandleBuyCardOption();
	void HandleUseCardOption(int option);

private:
	std::vector<std::shared_ptr<BaseCard>> _cardsInHand;
	bool _inUnoState = false;
	std::string _name;

	bool CanWin() const;
	void DispatchWinCondition();
	void HandleWinCondition(const std::shared_ptr<BaseCard> currentUseCard, int option);
	void HandleCardUsage(const std::shared_ptr<BaseCard> currentUseCard, int option);
	void TurnEnded();

public:
	explicit Player(std::shared_ptr<TurnHandler> turnHandler, const std::string& name);

	virtual ~Player() = default;
	virtual void StartTurn() = 0;
	virtual void AskToSelectAColor() = 0;

	void DrawCards() const;
	bool HasValidCardWithSymbolInHand();
	void AddCardToHand(std::shared_ptr<BaseCard> card);
	void SetUnoState(bool unoState);
	const std::vector<std::shared_ptr<BaseCard>>& GetCards() const;
	const std::shared_ptr<BaseCard>& GetCard(int index) const;
	void CleanPlayerHand();
	void ReplaceCardsInHand(const std::vector<std::shared_ptr<BaseCard>>& cards);
	const std::string& GetName() const;
};

