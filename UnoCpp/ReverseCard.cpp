#include "ReverseCard.h"
#include <memory>
#include "ReverseGameAction.h"
ReverseCard::ReverseCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	std::shared_ptr<ReverseGameAction> reverseGameAction = std::make_shared<ReverseGameAction>(_turnHandler);
	AddAction(reverseGameAction);
}