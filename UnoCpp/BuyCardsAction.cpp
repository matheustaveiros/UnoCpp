#include "BuyCardsAction.h"

BuyCardsAction::BuyCardsAction(int amount)
{
	_amount = amount;
}

void BuyCardsAction::Execute() {
	_turnHandler->BuyCardsFromDeck(_amount);
}