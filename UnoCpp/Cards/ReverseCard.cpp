#include <memory>
#include "Actions/ReverseGameAction.h"
#include "ReverseCard.h"
ReverseCard::ReverseCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto reverseGameAction = std::make_shared<ReverseGameAction>(_turnHandler);
	AddAction(reverseGameAction);
}