#include "PlusTwoCard.h"
#include <memory>
#include "BuyCardsAction.h"
#include "CheckForValidPlayAction.h"

PlusTwoCard::PlusTwoCard(std::shared_ptr<BaseCard> myPointer, Enums::CardColor color, std::string symbol) : BaseCard(myPointer, color, symbol)
{
	std::shared_ptr<BuyCardsAction> buyCardsAction = std::make_shared<BuyCardsAction>(_turnHandler, CARDS_TO_BUY);
	AddAction(buyCardsAction);

	std::shared_ptr<CheckForValidPlayAction> checkForValidPlayAction = std::make_shared<CheckForValidPlayAction>(_turnHandler);
	AddAction(checkForValidPlayAction);
}