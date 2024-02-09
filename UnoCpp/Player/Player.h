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
	TurnHandler* _turnHandler;

	void DrawTopCardFromDiscardPile();
	bool CardIsCompatible(BaseCard* card);
	bool CardIsSymbolOnlyCompatible(BaseCard* card);
	void HandleYellUnoOption();
	void HandleBuyCardOption();
	void HandleUseCardOption(int option);

private:
	std::vector<BaseCard*> _cardsInHand;
	bool _inUnoState = false;
	std::string _name;

	bool CanWin() const;
	void DispatchWinCondition();
	void HandleWinCondition(BaseCard* currentUseCard, int option);
	void HandleCardUsage(BaseCard* currentUseCard, int option);
	void TurnEnded();

public:
	explicit Player(TurnHandler* turnHandler, const std::string_view name);

	virtual ~Player() = default;
	virtual void StartTurn() = 0;
	virtual void AskToSelectAColor() = 0;
	virtual void AskForHandToSwap() = 0;

	void DrawCards();
	bool HasValidCardWithSymbolInHand();
	void AddCardToHand(BaseCard* card);
	void SetUnoState(bool unoState);
	std::span<BaseCard*> GetCards();
	BaseCard* GetCard(int index) const;
	void CleanPlayerHand();
	void ReplaceCardsInHand(const std::span<BaseCard*> cards);
	std::string_view GetName() const;
};

