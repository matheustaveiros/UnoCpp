#pragma once
#include "Player.h"
class AIPlayer : public Player
{

private:
	void CalculateThrowCardInput(bool checkSymbolOnly);
	void CalculateSelectColorInput();
	void SetUnoStateIfRequired();
	int GetBestCardOption(bool checkSymbolOnly);
	int GetAmountBySymbol(std::string_view symbol) const;
	int GetAmountByColor(const Enums::CardColor& color) const;
	Enums::CardColor GetColorByAmountInHand() const;
	int GetPlayerIndexWithLessCards();

public:
	AIPlayer(std::shared_ptr<TurnHandler> turnHandler, const std::string& name);
	void StartTurn() override;
	void AskToSelectAColor() override;
	void AskForHandToSwap() override;
};