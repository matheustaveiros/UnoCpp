#include "GoToNextPlayerAction.h"
void GoToNextPlayerAction::Execute() {
	_turnHandler->SkipToNextPlayer();
}