#pragma once
#include "BaseCard.h"
class PlusTwoCard : public BaseCard
{
private:
	const int CARDS_TO_BUY = 2;

public:
	PlusTwoCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol);
};

