#include <memory>
#include "Actions/GoToNextPlayerAction.h"
#include "NumberCard.h"

NumberCard::NumberCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);
}