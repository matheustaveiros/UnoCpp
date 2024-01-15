#include "JumpCard.h"
#include <memory>
#include "JumpPlayerAction.h"

JumpCard::JumpCard(std::shared_ptr<BaseCard> myPointer) : BaseCard(myPointer)
{
	std::shared_ptr<JumpPlayerAction> jumpPlayerAction = std::make_shared<JumpPlayerAction>(_turnHandler);
	AddAction(jumpPlayerAction);
}
