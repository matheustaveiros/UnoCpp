#include "SwapHandsAction.h"
SwapHandsAction::SwapHandsAction(TurnHandler* turnHandler) : BaseAction{ turnHandler }
{

}

void SwapHandsAction::Execute()
{
	_turnHandler->AskForHandToSwap();
}