#pragma once
#include "Player.h"
class AIPlayer : public Player
{

private:
	void CalculateThrowCardInput(bool checkSymbolOnly);
	void CalculateSelectColorInput();
	void SetUnoStateIfRequired();
	int GetBestCardOption(bool checkSymbolOnly);
	int GetAmountBySymbol(std::string_view symbol);
	int GetAmountByColor(const Enums::CardColor& color);
	Enums::CardColor GetColorByAmountInHand();
	int GetPlayerIndexWithLessCards() const;

public:
	AIPlayer(TurnHandler* turnHandler, const std::string_view name);
	void StartTurn() override;
	void AskToSelectAColor() override;
	void AskForHandToSwap() override;
};