#include "NumberCard.h"
#include <memory>
#include "GoToNextPlayerAction.h"

void NumberCard::Awake() {
	std::shared_ptr<GoToNextPlayerAction> goToNextPlayerAction = std::make_shared<GoToNextPlayerAction>(_turnHandler);
	AddAction(*goToNextPlayerAction.get());
}