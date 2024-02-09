#include <memory>
#include "Actions/BuyFromDiscardPileAction.h"
#include "Actions/CheckForValidPlayAction.h"
#include "Actions/GoToNextPlayerAction.h"
#include "BuyFromDiscardPileCard.h"

BuyFromDiscardPileCard::BuyFromDiscardPileCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol, int amountToBuy)
	: BaseCard(turnHandler, color, symbol), _cardsToBuy{ amountToBuy }
{
	auto buyCardsAction = std::make_shared<BuyFromDiscardPileAction>(_turnHandler, _cardsToBuy);
	AddAction(buyCardsAction);

	auto goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);

	auto checkForValidPlayAction = std::make_shared<CheckForValidPlayAction>(_turnHandler);
	AddAction(checkForValidPlayAction);
}