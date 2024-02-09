#include <memory>
#include "Actions/JumpPlayerAction.h"
#include "JumpCard.h"

JumpCard::JumpCard(TurnHandler* turnHandler, Enums::CardColor color, const std::string_view symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto jumpPlayerAction = std::make_unique<JumpPlayerAction>(_turnHandler);
	AddAction(jumpPlayerAction.get());
}
