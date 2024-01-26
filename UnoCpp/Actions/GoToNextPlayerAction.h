#pragma once
#include "BaseAction.h"
class GoToNextPlayerAction : public BaseAction
{
public:
	explicit GoToNextPlayerAction(std::shared_ptr<TurnHandler> turnHandler);
	void Execute() override;
};

