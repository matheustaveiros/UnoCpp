#include <memory>
#include "Actions/ReverseGameAction.h"
#include "ReverseCard.h"
ReverseCard::ReverseCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto reverseGameAction = std::make_shared<ReverseGameAction>(_turnHandler);
	AddAction(reverseGameAction);
}