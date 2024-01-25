#pragma once
#include "BaseCard.h"
class BuyFromDiscardPileCard : public BaseCard
{
private:
	int _cardsToBuy;

public:
	BuyFromDiscardPileCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol, int amountToBuy);
};

