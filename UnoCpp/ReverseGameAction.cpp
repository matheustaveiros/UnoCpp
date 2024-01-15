#include "ReverseGameAction.h"

ReverseGameAction::ReverseGameAction(std::shared_ptr<TurnHandler> turnHandler)
	: BaseAction(turnHandler)
{
}

void ReverseGameAction::Execute()
{
	_turnHandler->ReverseGame();
}