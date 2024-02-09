#pragma once
#include "BaseAction.h"
class CheckForValidPlayAction : public BaseAction
{
public:
	explicit CheckForValidPlayAction(TurnHandler* turnHandler);

	void Execute() override;
};

