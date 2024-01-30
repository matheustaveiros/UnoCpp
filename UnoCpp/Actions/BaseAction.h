#pragma once
#include <memory>
#include "Core/TurnHandler.h"

class TurnHandler;
class BaseAction
{
protected:
	std::shared_ptr<TurnHandler> _turnHandler;

public:
	explicit BaseAction(std::shared_ptr<TurnHandler> turnHandler);

	virtual void Execute() = 0;

	virtual ~BaseAction() = default;
};

