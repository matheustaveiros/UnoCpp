#include "BuyFromDiscardPileCard.h"
#include <memory>
#include "BuyFromDiscardPileAction.h"
#include "CheckForValidPlayAction.h"
#include "GoToNextPlayerAction.h"

BuyFromDiscardPileCard::BuyFromDiscardPileCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol, int amountToBuy)
	: BaseCard(turnHandler, color, symbol), _cardsToBuy{ amountToBuy }
{
	auto buyCardsAction = std::make_shared<BuyFromDiscardPileAction>(_turnHandler, _cardsToBuy);
	AddAction(buyCardsAction);

	auto goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);

	auto checkForValidPlayAction = std::make_shared<CheckForValidPlayAction>(_turnHandler);
	AddAction(checkForValidPlayAction);
}