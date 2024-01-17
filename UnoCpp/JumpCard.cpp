#include "JumpCard.h"
#include <memory>
#include "JumpPlayerAction.h"

JumpCard::JumpCard(std::shared_ptr<BaseCard> myPointer, Enums::CardColor color, std::string symbol) : BaseCard(myPointer, color, symbol)
{
	std::shared_ptr<JumpPlayerAction> jumpPlayerAction = std::make_shared<JumpPlayerAction>(_turnHandler);
	AddAction(jumpPlayerAction);
}
