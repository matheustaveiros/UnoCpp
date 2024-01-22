#include "PlusTwoCard.h"
#include <memory>
#include "BuyCardsAction.h"
#include "CheckForValidPlayAction.h"
#include "GoToNextPlayerAction.h"

PlusTwoCard::PlusTwoCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	std::shared_ptr<BuyCardsAction> buyCardsAction = std::make_shared<BuyCardsAction>(_turnHandler, CARDS_TO_BUY);
	AddAction(buyCardsAction);

	std::shared_ptr<GoToNextPlayerAction> goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);

	std::shared_ptr<CheckForValidPlayAction> checkForValidPlayAction = std::make_shared<CheckForValidPlayAction>(_turnHandler);
	AddAction(checkForValidPlayAction);
}