#include "AskForAColorAction.h"
AskForAColorAction::AskForAColorAction(std::shared_ptr<TurnHandler> turnHandler)
	: BaseAction(turnHandler)
{

}

void AskForAColorAction::Execute()
{
	_turnHandler->AskPlayerToSelectAColor();
}