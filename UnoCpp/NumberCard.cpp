#include "NumberCard.h"
#include <memory>
#include "GoToNextPlayerAction.h"

NumberCard::NumberCard(std::shared_ptr<BaseCard> myPointer) : BaseCard(myPointer)
{
	std::shared_ptr<GoToNextPlayerAction> goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(goToNextPlayerAction);
}