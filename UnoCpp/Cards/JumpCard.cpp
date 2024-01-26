#include <memory>
#include "../Actions/JumpPlayerAction.h"
#include "JumpCard.h"

JumpCard::JumpCard(std::shared_ptr<TurnHandler> turnHandler, Enums::CardColor color, const std::string& symbol)
	: BaseCard(turnHandler, color, symbol)
{
	auto jumpPlayerAction = std::make_shared<JumpPlayerAction>(_turnHandler);
	AddAction(jumpPlayerAction);
}
