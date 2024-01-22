#include "JumpPlayerAction.h"

JumpPlayerAction::JumpPlayerAction(std::shared_ptr<TurnHandler> turnHandler)
	: BaseAction(turnHandler)
{

}

void JumpPlayerAction::Execute()
{
	_turnHandler->JumpPlayer();
}