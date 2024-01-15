#pragma once
#include "BaseAction.h"
class JumpPlayerAction : public BaseAction
{
public:
	JumpPlayerAction(std::shared_ptr<TurnHandler> turnHandler);
	void Execute() override;
};

