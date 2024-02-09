#pragma once
#include "BaseAction.h"
class GoToNextPlayerAction : public BaseAction
{
public:
	explicit GoToNextPlayerAction(TurnHandler* turnHandler);
	void Execute() override;
};

