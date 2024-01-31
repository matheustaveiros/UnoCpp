#pragma once
#include "Player.h"
class AIPlayer : public Player
{

private:
	void CalculateThrowCardInput();
	void CalculateSelectColorInput();
	void SetUnoStateIfRequired();
	int GetBestCardOption();
	int GetAmountBySymbol(std::string_view symbol) const;
	int GetAmountByColor(const Enums::CardColor& color) const;
	Enums::CardColor GetColorByAmountInHand() const;
};