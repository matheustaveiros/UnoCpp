#include <memory>
#include "Actions/BuyCardsAction.h"
#include "Actions/CheckForValidPlayAction.h"
#include "Actions/GoToNextPlayerAction.h"
#include "Actions/AskForAColorAction.h"
#include "PlusFourCard.h"

PlusFourCard::PlusFourCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto buyCardsAction = std::make_unique<BuyCardsAction>(_turnHandler, CARDS_TO_BUY);
	AddAction(buyCardsAction.get());

	auto askForAColorAction = std::make_unique<AskForAColorAction>(_turnHandler);
	AddAction(askForAColorAction.get());

	auto goToNextPlayerAction = std::make_unique<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction.get());

	auto checkForValidPlayAction = std::make_unique<CheckForValidPlayAction>(_turnHandler);
	AddAction(checkForValidPlayAction.get());

}