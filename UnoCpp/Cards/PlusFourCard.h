#pragma once
#include "BaseCard.h"
class PlusFourCard : public BaseCard
{
private:
	const int CARDS_TO_BUY = 4;

public:
	PlusFourCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol);
};