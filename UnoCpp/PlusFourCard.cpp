#include <memory>
#include "BuyCardsAction.h"
#include "CheckForValidPlayAction.h"
#include "GoToNextPlayerAction.h"
#include "AskForAColorAction.h"
#include "PlusFourCard.h"

PlusFourCard::PlusFourCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto buyCardsAction = std::make_shared<BuyCardsAction>(_turnHandler, CARDS_TO_BUY);
	AddAction(buyCardsAction);

	auto goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);

	auto checkForValidPlayAction = std::make_shared<CheckForValidPlayAction>(_turnHandler);
	AddAction(checkForValidPlayAction);

	auto askForAColorAction = std::make_shared<AskForAColorAction>(_turnHandler);
	AddAction(askForAColorAction);
}