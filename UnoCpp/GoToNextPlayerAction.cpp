#include "GoToNextPlayerAction.h"

GoToNextPlayerAction::GoToNextPlayerAction(std::shared_ptr<TurnHandler> turnHandler)
	: BaseAction(turnHandler)
{
}

void GoToNextPlayerAction::Execute() {
	_turnHandler->SkipToNextPlayer();
}