#include "JumpPlayerAction.h"

JumpPlayerAction::JumpPlayerAction(TurnHandler* turnHandler)
	: BaseAction(turnHandler)
{

}

void JumpPlayerAction::Execute()
{
	_turnHandler->JumpPlayer();
}