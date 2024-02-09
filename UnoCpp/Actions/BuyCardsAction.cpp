#include "BuyCardsAction.h"
BuyCardsAction::BuyCardsAction(TurnHandler* turnHandler, int amount) : BaseAction{ turnHandler }, _amount { amount }
{
	
}

void BuyCardsAction::Execute()
{
	_turnHandler->BuyCardsAndAddInStackPile(_amount);
}