#include "CheckForValidPlayAction.h"

CheckForValidPlayAction::CheckForValidPlayAction(std::shared_ptr<TurnHandler> turnHandler)
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