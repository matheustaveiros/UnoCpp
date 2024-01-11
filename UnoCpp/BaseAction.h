#pragma once
#include "TurnHandler.h"
class BaseAction
{
public:
	BaseAction(TurnHandler& _turnHandler) {

	}

	virtual void Execute() = 0;
};

