#include "PlusTwoCard.h"
#include <memory>
#include "BuyCardsAction.h"

void PlusTwoCard::Awake() {
	std::shared_ptr<BuyCardsAction> buyCardsAction = std::make_shared<BuyCardsAction>(_turnHandler);
	AddAction(*buyCardsAction);
}