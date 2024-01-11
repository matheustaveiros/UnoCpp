#include "BaseAction.h"

BaseAction::BaseAction(std::shared_ptr<TurnHandler> turnHandler)
{
	_turnHandler = turnHandler;
}
