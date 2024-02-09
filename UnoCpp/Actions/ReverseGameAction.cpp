#include "ReverseGameAction.h"

ReverseGameAction::ReverseGameAction(TurnHandler* turnHandler)
	: BaseAction(turnHandler)
{

}

void ReverseGameAction::Execute()
{
	_turnHandler->ReverseGame();
}