#include "NumberCard.h"
#include <memory>
#include "GoToNextPlayerAction.h"

NumberCard::NumberCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, std::string symbol)
	: BaseCard(turnHandler, color, symbol)
{
	std::shared_ptr<GoToNextPlayerAction> goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);
}