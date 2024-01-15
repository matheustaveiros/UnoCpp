#pragma once
#include "BaseAction.h"
class CheckForValidPlayAction : public BaseAction
{
public:
	CheckForValidPlayAction(std::shared_ptr<TurnHandler> turnHandler);

	void Execute() override;
};

