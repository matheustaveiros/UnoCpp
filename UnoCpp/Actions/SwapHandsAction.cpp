#include "SwapHandsAction.h"
SwapHandsAction::SwapHandsAction(std::shared_ptr<TurnHandler> turnHandler) : BaseAction{ turnHandler }
{

}

void SwapHandsAction::Execute()
{
	_turnHandler->AskForHandToSwap();
}