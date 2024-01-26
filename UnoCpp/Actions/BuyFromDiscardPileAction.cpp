#include "BuyFromDiscardPileAction.h"
BuyFromDiscardPileAction::BuyFromDiscardPileAction(std::shared_ptr<TurnHandler> turnHandler, int amount) : BaseAction{ turnHandler }, _amount{ amount }
{

}

void BuyFromDiscardPileAction::Execute()
{
	_turnHandler->BuyCardsFromDiscardPile(_amount);
}