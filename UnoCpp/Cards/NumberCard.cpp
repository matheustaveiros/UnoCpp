#include <memory>
#include "Actions/GoToNextPlayerAction.h"
#include "NumberCard.h"

NumberCard::NumberCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto goToNextPlayerAction = std::make_unique<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction.get());
}