#include "ReverseCard.h"
#include <memory>
#include "ReverseGameAction.h"
ReverseCard::ReverseCard(std::shared_ptr<TurnHandler> turnHandler, std::shared_ptr<BaseCard> myPointer, Enums::CardColor color, std::string symbol)
	: BaseCard(turnHandler, myPointer, color, symbol)
{
	std::shared_ptr<ReverseGameAction> reverseGameAction = std::make_shared<ReverseGameAction>(_turnHandler);
	AddAction(reverseGameAction);
}