#include "ReverseCard.h"
#include <memory>
#include "ReverseGameAction.h"
void ReverseCard::Awake() {
	std::shared_ptr<ReverseGameAction> reverseGameAction = std::make_shared<ReverseGameAction>(_turnHandler);
	AddAction(*reverseGameAction.get());
}