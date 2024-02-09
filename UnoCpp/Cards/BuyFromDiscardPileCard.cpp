#include <memory>
#include "Actions/BuyFromDiscardPileAction.h"
#include "Actions/CheckForValidPlayAction.h"
#include "Actions/GoToNextPlayerAction.h"
#include "BuyFromDiscardPileCard.h"

BuyFromDiscardPileCard::BuyFromDiscardPileCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol, int amountToBuy)
	: BaseCard(turnHandler, color, symbol), _cardsToBuy{ amountToBuy }
{
	auto buyCardsAction = std::make_unique<BuyFromDiscardPileAction>(_turnHandler, _cardsToBuy);
	AddAction(buyCardsAction.get());

	auto goToNextPlayerAction = std::make_unique<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction.get());

	auto checkForValidPlayAction = std::make_unique<CheckForValidPlayAction>(_turnHandler);
	AddAction(checkForValidPlayAction.get());
}