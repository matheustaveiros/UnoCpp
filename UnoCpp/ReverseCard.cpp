#include "ReverseCard.h"
#include <memory>
#include "ReverseGameAction.h"
ReverseCard::ReverseCard(std::shared_ptr<BaseCard> myPointer) : BaseCard(myPointer)
{
	std::shared_ptr<ReverseGameAction> reverseGameAction = std::make_shared<ReverseGameAction>(_turnHandler);
	AddAction(reverseGameAction);
}