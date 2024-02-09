#include "GoToNextPlayerAction.h"

GoToNextPlayerAction::GoToNextPlayerAction(TurnHandler* turnHandler)
	: BaseAction(turnHandler)
{

}

void GoToNextPlayerAction::Execute()
{
	_turnHandler->SkipToNextPlayer();
}