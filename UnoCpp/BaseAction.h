#pragma once
#include <memory>
#include "TurnHandler.h"

class TurnHandler;
class BaseAction
{

public:
	explicit BaseAction(std::shared_ptr<TurnHandler> turnHandler);

	virtual void Execute() = 0;

	virtual ~BaseAction() = default;

	std::shared_ptr<TurnHandler> _turnHandler;
};

