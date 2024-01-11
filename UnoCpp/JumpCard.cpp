#include "JumpCard.h"
#include <memory>
#include "JumpPlayerAction.h"

void JumpCard::Awake() {
	std::shared_ptr<JumpPlayerAction> jumpPlayerAction = std::make_shared<JumpPlayerAction>(_turnHandler);
	AddAction(*jumpPlayerAction);
}
