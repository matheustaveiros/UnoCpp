#include "CheckForValidPlayAction.h"

CheckForValidPlayAction::CheckForValidPlayAction(TurnHandler* turnHandler)
	: BaseAction(turnHandler)
{

}

void CheckForValidPlayAction::Execute()
{
	if (!_turnHandler->HasValidCard())
	{
		_turnHandler->ApplyStackCardsToPlayer();
		_turnHandler->SkipToNextPlayer();
	}
}