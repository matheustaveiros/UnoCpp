#include <memory>
#include "Actions/ReverseGameAction.h"
#include "ReverseCard.h"
ReverseCard::ReverseCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto reverseGameAction = std::make_unique<ReverseGameAction>(_turnHandler);
	AddAction(reverseGameAction.get());
}