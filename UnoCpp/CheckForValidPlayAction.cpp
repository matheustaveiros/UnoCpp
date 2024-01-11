#include "CheckForValidPlayAction.h"
void CheckForValidPlayAction::Execute() {
	if (!_turnHandler->HasValidCard())
	{
		_turnHandler->ApplyStackCardsToPlayer();
		_turnHandler->SkipToNextPlayer();
	}
}