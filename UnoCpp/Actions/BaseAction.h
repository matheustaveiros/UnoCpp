#pragma once
#include <memory>
#include "Core/TurnHandler.h"

class TurnHandler;
class BaseAction
{
protected:
	TurnHandler* _turnHandler;

public:
	explicit BaseAction(TurnHandler* turnHandler);

	virtual void Execute() = 0;

	virtual ~BaseAction() = default;
};

