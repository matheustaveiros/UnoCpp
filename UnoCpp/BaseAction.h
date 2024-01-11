#pragma once
#include "TurnHandler.h"
#include "memory"
class BaseAction
{

public:
	BaseAction(std::shared_ptr<TurnHandler> turnHandler);

	virtual void Execute() = 0;

	BaseAction() = default;
	virtual ~BaseAction() = default;

protected:
	std::shared_ptr<TurnHandler> _turnHandler;
};

