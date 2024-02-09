#include "AskForAColorAction.h"

AskForAColorAction::AskForAColorAction(TurnHandler* turnHandler)
	: BaseAction(turnHandler)
{

}

void AskForAColorAction::Execute()
{
	_turnHandler->AskPlayerToSelectAColor();
}