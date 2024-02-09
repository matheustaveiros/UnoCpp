#pragma once
#include "BaseCard.h"
class BuyFromDiscardPileCard : public BaseCard
{
private:
	int _cardsToBuy;

public:
	BuyFromDiscardPileCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol, int amountToBuy);
};

