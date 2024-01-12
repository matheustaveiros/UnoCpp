#pragma once
#include <memory>
#include "TurnHandler.h"

class TurnHandler;
class BaseAction
{

public:
	BaseAction(std::shared_ptr<TurnHandler> turnHandler) : _turnHandler{ turnHandler } { }

	virtual void Execute() = 0;

	virtual ~BaseAction() = default;

	std::shared_ptr<TurnHandler> _turnHandler;
};

