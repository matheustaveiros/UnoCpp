#include "BuyCardsAction.h"
BuyCardsAction::BuyCardsAction(std::shared_ptr<TurnHandler> turnHandler, int amount) : BaseAction{ turnHandler }, _amount { amount }
{
	
}

void BuyCardsAction::Execute() {
	_turnHandler->BuyCardsFromDeck(_amount);
}