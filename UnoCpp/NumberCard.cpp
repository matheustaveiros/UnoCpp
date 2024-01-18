#include "NumberCard.h"
#include <memory>
#include "GoToNextPlayerAction.h"

NumberCard::NumberCard(std::shared_ptr<TurnHandler> turnHandler, std::shared_ptr<BaseCard> myPointer, Enums::CardColor color, std::string symbol)
	: BaseCard(turnHandler, myPointer, color, symbol)
{
	std::shared_ptr<GoToNextPlayerAction> goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);
}